# RazSystems - UE 5.8 Weapon Plugins

Collection of data-driven plugins for building weapons, magazines and ammo in Unreal Engine 5.8. Everything is structured around Primary Data Assets so you can configure firearms in the editor without touching C++.

## Plugins

**AmmoSystem** - Defines two asset types:

- **Calibre** - represents a physical cartridge (5.56x45, 9x19, etc). This is the shared key that links ammo, magazines and weapons together. If two things point at the same Calibre asset they're compatible, if they don't they aren't.
- **Ammo** - a specific round. Holds damage, penetration, and a reference to its Calibre.


**MagazineSystem** - Depends on AmmoSystem.

- **Magazine** - capacity, display name, and a Calibre reference. A magazine only fits a weapon that shares the same Calibre asset.


**WeaponSystemBase** - Depends on AmmoSystem + MagazineSystem.

- **Weapon** - skeletal mesh (soft reference, streamed in on equip), fire rate, Calibre, and an optional default magazine.


**WeaponSystemAttachments** - Extends WeaponSystemBase. Attachment support, still in progress.

**RazPluginNamingConvention** - Adds basic linting to names to stop malformed naming conventions.

- **Convention** Runs automatically on save and on "Validate Assets". Rejects any `PDA_` asset whose name doesn't match the convention for its type, with a per-token error message so you know exactly which part is wrong.


## Setup

Clone the whole `Plugins/` folder into your project:

```
YourProject/
  Plugins/
    AmmoSystem/
    MagazineSystem/
    WeaponSystemBase/
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
└── WeaponSystem
      └── Weapon
```

## Naming Convention

All assets follow `PDA_<Type>_<...fields...>`. The optional naming convention plugin enforces this on save.

| Type | Format | Example |
|---|---|---|
| Calibre | `PDA_Calibre_<NNxNN>` | `PDA_Calibre_556x45` |
| Ammo | `PDA_Ammo_<Calibre>_<Damage>_<Penetration>_<Name>` | `PDA_Ammo_556x45_46_28_M855` |
| Magazine | `PDA_Mag_<Calibre>_<Capacity>_<Name>` | `PDA_Mag_556x45_030_Stanag` |
| Weapon | `PDA_Weapon_<Calibre>_<FireRate>_<Name>` | `PDA_Weapon_556x45_800_M4A1` |

Calibre uses the format `NxN` (digits, x, digits). Magazine capacity is zero-padded to 3 digits. Names are alphanumeric and can start with a number (e.g. `6LG1`).

## How Compatibility Works

Calibre identity is just a pointer comparison at runtime:

```cpp
if (Magazine->Calibre == Weapon->Calibre)
{
      // Reload weapon for example
}
```

A 7.62x54R magazine and a 7.62x51 NATO weapon will never match even though the numbers look similar same with 7.92x57 and 7.62×25, because they point to different Calibre assets. No string parsing, no enums to maintain.

## Dependencies

```
AmmoSystem
└── MagazineSystem
      └── WeaponSystemBase
            └── WeaponSystemAttachments
```
