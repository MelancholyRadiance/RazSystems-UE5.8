# RazSystems - UE 5.8 Weapon Plugins

Collection of data-driven plugins for building weapons, magazines and ammo in Unreal Engine 5.8. Everything is structured around Primary Data Assets so you can configure firearms in the editor without touching C++.

## Plugins

**AmmoSystem** - Defines two asset types:

- **Calibre** - represents a physical cartridge (5.56x45, 9x19, etc). This is the shared key that links ammo, magazines and weapons together. If two things point at the same Calibre asset they're compatible, if they don't they aren't.
- **Ammo** - a specific round. Holds damage, penetration, and a reference to its Calibre.

**MagazineSystem** - Depends on AmmoSystem.

- **Magazine** - capacity, display name, and a Calibre reference. A magazine only fits a weapon that shares the same Calibre asset.

**WeaponSystemBase** - Depends on AmmoSystem + MagazineSystem.

- **Weapon** - skeletal mesh (soft reference, streamed in on equip), fallback fire rate, Calibre, default magazine, and an optional list of fire mode assets.

**FireModeSystem** - Optional extension to WeaponSystemBase. Defines fire mode data assets and the runtime logic that drives them.

- **Semi Automatic** - one shot per trigger press with a configurable RPM cap to prevent auto-clicking.
- **Burst Fire** - fixed shot count per trigger press, with configurable rate, cooldown, and an optional continuous mode that keeps bursting while the trigger is held. Supports an optional RPM curve across the burst.
- **Fully Automatic** - fires continuously while the trigger is held at a set RPM. Supports an optional wind-up curve (RPM ramps up over time).

Add a `FireModeManagerComponent` to your weapon actor, populate its `FireModes` array with your assets, and bind `OnFireShot` to your shot logic. Call `StartFire()` / `StopFire()` from input and `CycleFireMode()` to switch modes.

**MovementSystem** - Standalone, no dependencies on the weapon plugins.

- Add `RazMovementDataComponent` to any Character. Populate whichever slots you need and call the functions from input or your character class.
- **Jump** - sets Z velocity and max jump count on the CMC.
- **Sprint** - speed multiplier with optional ramp-up curve (X = seconds sprinting, Y = multiplier).
- **Crouch** - uses UE's native Crouch/UnCrouch so the capsule resize is replicated automatically. Multiplier with optional curve.
- **Prone** - manual capsule resize driven by a replicated bool. Fine for most games, less authoritative than native crouch in competitive multiplayer. Multiplier with optional curve.
- **Aim** - flat speed multiplier applied while aiming down sights.
- **Inertia** - a single asset that sets max acceleration, braking, ground friction, air control and braking while falling. Think of it as the weight profile of your character.

Sprint, Crouch, Prone and Aim all stack multiplicatively - they are not mutually exclusive. A character can sprint + aim at the same time and get both multipliers applied.

**WeaponSystemAttachments** - Extends WeaponSystemBase. Attachment support, still in progress.

**RazPluginNamingConvention** - Adds basic linting to names to stop malformed naming conventions.

- Runs automatically on save and on "Validate Assets". Rejects any `PDA_` asset whose name doesn't match the convention for its type, with a per-token error message so you know exactly which part is wrong.

## Setup

Clone the whole `Plugins/` folder into your project:

```
YourProject/
  Plugins/
    AmmoSystem/
    MagazineSystem/
    WeaponSystemBase/
    FireModeSystem/              (optional)
    MovementSystem/              (optional)
    WeaponSystemAttachments/     (optional)
    RazPluginNamingConvention/   (optional)
```

On first launch Unreal will ask to rebuild the modules, say yes. Requires Visual Studio with the C++ workload installed.

## Creating Assets

Right-click in the Content Browser and look for the **RazSystems** category. Assets are grouped by plugin:

```
RazSystems
├── AmmoSystem
│     ├── Calibre
│     └── Ammo
├── MagazineSystem
│     └── Magazine
├── WeaponSystem
│     └── Weapon
└── FireModeSystem
│     ├── Semi Automatic
│     ├── Burst Fire
│     └── Fully Automatic
└── MovementSystem
      ├── Jump Data
      ├── Sprint Data
      ├── Crouch Data
      ├── Prone Data
      ├── Aim Data
      └── Movement Inertia Data
```

## Naming Convention

All assets follow `PDA_<Type>_<...fields...>`. The optional naming convention plugin enforces this on save.

| Type | Format | Example |
|---|---|---|
| Calibre | `PDA_Calibre_<NNxNN>` | `PDA_Calibre_556x45` |
| Ammo | `PDA_Ammo_<Calibre>_<Damage>_<Penetration>_<Name>` | `PDA_Ammo_556x45_46_28_M855` |
| Magazine | `PDA_Mag_<Calibre>_<Capacity>_<Name>` | `PDA_Mag_556x45_030_Stanag` |
| Weapon | `PDA_Weapon_<Calibre>_<FireRate>_<Name>` | `PDA_Weapon_556x45_800_M4A1` |
| Semi Auto | `PDA_SemiAuto_<MaxRate>` | `PDA_SemiAuto_600` |
| Burst | `PDA_Burst_<Count>_<Continuous>_<Rate>` | `PDA_Burst_3_0_900` |
| Full Auto | `PDA_FullAuto_<Rate>` | `PDA_FullAuto_800` |
| Jump | `PDA_Jump_<ZVelocity>_<MaxJumpCount>` | `PDA_Jump_600_1` |
| Sprint | `PDA_Sprint_<SpeedMultiplierPercent>` | `PDA_Sprint_150` |
| Crouch | `PDA_Crouch_<SpeedMultiplierPercent>` | `PDA_Crouch_50` |
| Prone | `PDA_Prone_<SpeedMultiplierPercent>` | `PDA_Prone_15` |
| Aim | `PDA_Aim_<SpeedMultiplierPercent>` | `PDA_Aim_70` |
| Inertia | `PDA_Inertia_<Name>` | `PDA_Inertia_Standard` |

Calibre uses the format `NxN` (digits, x, digits). Magazine capacity is zero-padded to 3 digits. Names are alphanumeric and can start with a number (e.g. `6LG1`). Burst continuous is `0` (single burst per press) or `1` (hold to keep bursting).

## How Compatibility Works

Calibre identity is just a pointer comparison at runtime:

```cpp
if (Magazine->Calibre == Weapon->Calibre)
{
    // Reload weapon for example
}
```

A 7.62x54R magazine and a 7.62x51 NATO weapon will never match even though the numbers look similar, because they point to different Calibre assets. No string parsing, no enums to maintain.

## What Goes Where

**On the weapon actor** - `FireModeManagerComponent`, reference to its `PDAWeaponData`, shot logic bound to `OnFireShot`, current magazine state.

**On the character** - reference to the equipped weapon, input events that call through to the weapon (`StartFire`, `StopFire`, `CycleFireMode`), magazine inventory and reload logic, `RazMovementDataComponent` for movement state.

## Dependencies

```
AmmoSystem
└── MagazineSystem
      └── WeaponSystemBase
            ├── FireModeSystem          (optional)
            └── WeaponSystemAttachments (optional)

MovementSystem  (standalone, no weapon system dependencies)
```
