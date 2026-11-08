# Controller Focus

A Windows Geode mod by piraxxs. Geometry Dash only processes controllers while its window is in the foreground.

## Install

Requires Geometry Dash 2.2081 and Geode 5.8.2 (compatible 5.x).

1. Close Geometry Dash.
2. Copy `piraxxs.controller_focus.geode` into `Geometry Dash/geode/mods/`.
3. Start the game. No settings are required.

All controller processing is gated together: face buttons, Back, Start, shoulders, triggers, D-pad, both sticks, and controller-generated mouse actions. Other games retain access to the controller.

After returning to Geometry Dash, release every button and trigger and center both sticks once. This prevents a button held in another game from triggering a menu or gameplay action on return. Small stick drift inside Geode's deadzone is accepted. Each controller rearms independently.

This mod gates Geometry Dash's native/Geode controller path. Separate tools that translate controller input into keyboard or mouse events, or mods that poll controllers independently, may need their own focus settings.

## Build

Install the Geode SDK and CLI, CMake 3.25+, and a C++23-capable Visual Studio toolchain. Set `GEODE_SDK` to the SDK directory.

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

The `.geode` package is generated in `build/`. Building does not install it automatically.

Standalone transition tests without the SDK:

```powershell
cmake -S . -B build-tests -DFOCUS_GUARD_TESTS_ONLY=ON
cmake --build build-tests --config Release
ctest --test-dir build-tests -C Release --output-on-failure
```

## Manual verification before publication

- With GD focused, check gameplay, menu navigation, Back/Start, sticks and mouse control.
- Alt-Tab to another app and exercise every controller control. GD must receive no new controller actions and must not generate Windows mouse movement or clicks.
- Return while holding a button, trigger or stick. GD must wait for neutral before accepting a fresh press.
- Repeat with GD minimized, controller disconnect/reconnect and two controllers.
- Test alongside your installed input-related mods.

Automated tests cover the focus/rearm state machine; they do not replace live controller testing.
