Changelog

0.2.1-fbt.1

Unofficial build by Syncher-source: dariulone's 0.2.1 with full-body tracking, finger tracking and the HUD work added. Report problems with this build to Syncher-source, not to dariulone. Full-body tracking reports go to github.com/Syncher-source/cyberpunk-fbt-lab.

Added
- Full-body tracking: three Vive Trackers (waist, left foot, right foot) drive V's legs, hips and spine, and V's arms reach the controllers. Calibrated in game in three steps, with the texts in all 18 languages. Off until it is set up; without trackers nothing changes. Tested walking around a room; swimming, driving, ladders, sitting and takedowns are still being tested and may need fixes. Setup: give the trackers the roles Waist, Left Foot and Right Foot in SteamVR, set xr_vive_trackers=1 in red4ext\plugins\cyberpunkvrport\config\vrport.ini and restart the game, load a save, turn on the three full-body switches in the settings, then run the calibration. Calibrate at every session.
- Finger tracking: each of V's fingers follows yours, with finger-tracking gloves and Valve Index controllers (OpenXR hand tracking). The grip can come from a fist or a thumbs-up instead of the grip sensor, and the fingers can spread sideways. Off by default; turning it on applies at the next game start.
- The HUD stays in front of the world: near a wall, a door or a person it comes in just in front of them, and goes back out when there is room. Off by default.
- Your hands push the HUD out of view while they are in front of it, so it never covers them. Off by default.
- The interaction prompt can sit on the object it names, instead of at a fixed distance. Off by default.
- CPU affinity, for power users, in vrport.ini only: xr_cpu_affinity=1 keeps the game on the CPUs with the largest L3 cache (the V-cache side of a 7950X3D or 9950X3D), and does nothing when the caches are the same size. A hex mask sets the CPUs by hand. Off by default; applies at the next game start.

Fixed
- With the interaction and loot panels locked to the head, the main HUD still trailed behind them, because its free-look cone stopped at 5 degrees. The cone now goes down to 0, which locks the main HUD to the head too.
- Arm cyberware could be selected but not used on some characters: with the mantis blades (or other arm cyberware) out the arms fell back to the game's flat idle, blocking worked and attacks did not. The port let go of the arms when the character's skeleton was over 800 bones, and what V wears counts: clothing with many bones of its own plus the implant's went past it, which is why it followed certain saves. The limit is now 2048.
- Saves of a female V loaded as a bald man without her cyberware (0.2.0's lobby body file swapped the game's default body gender, and a save stores V's gender only as a difference from it). Women's and men's saves load as they were saved again, nothing in the saves is changed, and the lobby's own body no longer touches the game's records. The leftover file of 0.2.0 is deleted on start when 0.2.1 is unpacked over it.
- Going back from a game to the main menu left the lobby's menu dead: nothing could be pressed any more.
- A crash when a new game started from the lobby (the weather was read while the session changed).
- Saves whose wardrobe set names clothes from a mod that is no longer installed: V stood undressed. The set is taken off before the clothes are put on at load, so the real clothes are there, pants and shoes too; the set stays in the wardrobe for when the mod returns.
- A female V wearing nothing on the legs but underwear had no torso, legs or belly in the first person, only floating feet - the game itself takes that body part off then
- The neck cap was a different skin colour from the body: it now takes the body's own skin material and tone, textured and lit like the skin of the upper chest.
- A crash on returning to the main menu, in the game's cyberware appearance restore running on a system that had already left the game.
- The sticks and buttons stopped walking and steering the car when the game's window on the monitor was not in front - after a click on another window or screen, the runtime's or a streaming app's window, or the game minimising itself. The game drops the pad's events then; while the headset has the input they now reach it whatever window is in front.
- The cyberware chord (left grip + left stick click, held half a second) did nothing when the game's window was not in front: it was a key press, and a key only reaches the window in front. With the window behind, the chord now runs the game's own activation of the operating system (Sandevistan, Berserk, overclock) directly, with the same checks.
- L3 + R3 did not open the VR menu while a weapon was drawn. The chord now holsters and opens the menu once the hands are free.
- Cyber Engine Tweaks' console and windows could not be used: the port's own Lua windows opened on CET's key, lay over CET's and took its mouse and keyboard. CET keeps its key and its input now; the port's windows have their own key (Scroll Lock beside CET, Home without it, config\lua_bindings.json), and CET's key closes them.
- The port's Lua windows: the pointer was stuck in the middle of the screen, V also turned, walked and fired behind them, and all of them opened on one spot.
- Dual wielding: since 0.2.0 the left hand held its gun the wrong way, off the grip with the fingers open around it. The player's body had lost the game's dual wield animations.
- Dual wielding: the left gun fired at a lighter pull than the right one. Both triggers now fire at the same point.
- Dual wielding: bringing the left hand close to the right gun opened its fingers, and the grip button there stuck the left hand to the right gun.
- SteamVR: the world was upside down at the start until the view was recentred

0.2.0

New
- One requirement: RED4ext 1.31.0. Cyber Engine Tweaks, ArchiveXL, TweakXL, Input Loader, Codeware and redscript are no longer needed - the plugin runs the port's Lua mods in its own host, mounts its archive and applies its manifest, applies its TweakDB records, merges its input bindings, provides the natives the scripts used Codeware for, and compiles the scripts with redscript's compiler built in. Installed frameworks keep working beside it.
- A VR lobby in the main menu: the game starts in the dark with its legal notice and logo hung in front of you (free look, mono, with their own sounds), then fades into a hall you can walk. Its holographic menu lists saves under their playthroughs with a preview of each, the game's and the port's settings as its own pages, and starts a new game in VR - life path cards, then character creation in a window 1.5 m away where the figure steps up to the part you point at. A save is an engram you put in to become that V. Items on the table can be picked up (a procedural grasp for every kind), including the Maelstrom chibi and Skippy. The lobby has its own ambience and music on the game's sliders, and a loudspeaker button to turn it off.
- No splash, start screen or loading screen in the headset at boot; loading screens hang in the dark 3 m ahead in stereo, read through their mip chain so the text stays sharp.
- First-launch setup in the headset: the weapon hand chosen on two cards, the T-pose and your height, before the lobby's menu; the body is sized from the height.
- Left-handed mode: the controllers trade roles and the prompts show the buttons pressed, the weapon is held and animated in the left hand (mirrored animations, melee too), the right hand reloads and holds the magazine mirrored, the belt carries magazines on the right hip and grenades on the left, and smoking puts the cigarette in the left hand.
- Reach: a free hand points at things in the world with a small marker, the grip takes what the game offers, and a pointed item snatched toward the body flies to the palm. A hand that already holds something takes nothing.
- Weapon wheel on a held Y, in front of the weapon hand, without the game's pause: weapon wedges, the hotkey arcs, a holster wedge, a grenade row and the cigarette.
- Reload hints: the part the hand should pull glows while rounds wait on the slide, a dry magazine glows, and a dropped one stays as an outline.
- A neck cap in the first-person body: looking down no longer looks into the chest. Slides, jumps, falls and landings draw the animation's own torso under the view.
- Water reflections are rendered per eye in engine stereo.
- Haptics for melee hits and swings in the weapon hand.
- PS VR2 Sense shortcuts, Toolkit haptics and FOV presets (contributed, PR #96).
- The view recentres by itself when the headset is put back on, and hands returning into tracking glide back instead of jumping.
- The aiming dot is drawn in both eyes of engine stereo, and its toggle is saved.
- Braindance on controllers without shoulder buttons: the left grip is LB (editor mode) and the right grip RB (layer). The VR menu does not open in a braindance.
- The launcher is redrawn: dark, with a DPI-aware layout. Up to 3500 px the resolution steps are at most 1.12 per side, so the ladders now have 188 resolutions for the 19 headsets. 49 of them need engine stereo (the default) and are not listed when it is off.

Performance
- The camera scope's render graph runs its nodes in parallel like the main view's instead of one after another: on the Grad in the megabuilding 26.2 -> 18.5 ms (38 -> 53 FPS), with the GPU busier and the same lens image.
- The Lua mods' garbage collector runs while the game thread waits for the world tick, and every binding call is cheaper.
- The submission chain and deferred present are on by default again; world touch and the optics do less work per frame on the game thread.
- Frame generation defaults to NVIDIA optical flow at half resolution with FidelityFX interpolation.
- The VR menu reacts to a click in about 10 ms instead of 80, and no longer freezes on the Lua collector.

Fixed
- A crash right after a braindance ended (engine stereo).
- The release zip stored its paths with backslashes, which unpackers that follow the zip spec turned into long file names instead of folders (issue #145).
- The braindance HUD sat higher than the scanner's centre on headsets whose lenses look further down than up.
- A ladder climb's last pull, or a hand letting go of the steering wheel, could open the VR menu at the top.
- A crash while loading a save with the tactical belt (a second attach request freed the half-loaded belt).
- Images in the VR menu dimmed every 7 seconds.
- The menu pointer moved with head turns; it now leaves the controller's wrist.
- Quest Touch shoulder buttons did not work in menus.
- Scaled or moved HUD elements were clipped at the canvas edge.
- Pump shotguns and the Grad played their cycle sounds before the hand worked the action; the revolver's crane is shut by the hand's motion; the slide could not be taken after a reach.
- Engine stereo DLSS copied back more than its scaling output.
- The window starts borderless on every launch, and the eye size is fitted to what the OpenXR runtime accepts.

Changed
- The plugin is red4ext\plugins\cyberpunkvrport\cyberpunkvrport.dll (it was CyberpunkVR_Stereo.dll), in one folder with its shaders, grips, archive, config and log. An old CyberpunkVR_Stereo.dll left in that folder is renamed to .old at the first start; when it had already started, this launch runs it and the next one runs the new plugin.
- The on-foot capsule radius is 0.25 m, and the head leans past a blocked capsule instead of being held on it.
- engine\config\platform\pc\vrcam_cpu_tweaks.ini is no longer installed; delete it when upgrading (UNINSTALL.bat removes it too).

0.1.9

New
- Cyberpunk 2077 2.5. The port is rebuilt for the 2.5 executable (addresses, view and camera layouts, constant buffers, SDK structures and every shader twin regenerated for 2.5). 2.31 is no longer supported. On a game build it was not made for, the plugin now installs no hooks and says so in a message box instead of patching the wrong addresses.
- Engine stereo: both eyes are rendered by the game's own side-by-side stereo renderer (the 2.5 render feature 98) in one frame, each eye with its own lens window and its own DLSS. No Odyssey 3D SDK, registry key or extra ini is needed. On by default (xr_engine_stereo); splash screens, intros and the first loading screen are shown mono, and stereo starts at the main menu. The second-view stereo of 0.1.8 is still available with xr_engine_stereo=0.
- Under engine stereo the HUD and notifications are laid out one eye wide, world markers are reprojected into each eye, frame generation and foveated DLSS work per eye, and the work that only the old second view needed is skipped.
- Mono mode (Settings > Stereo > "Mono mode", xr_mono_mode): one picture for both eyes, drawn once from the head centre - no depth, the most frames. Under engine stereo it applies after a restart.
- VR menu: hold L3 + R3 for half a second. A holographic menu in the world, used with the index fingertip or the hand ray and trigger: inventory and equipment with the game's own item tooltips (also on hover on the equipment page), the backpack (crafting components, filters, sort, favourite, drop, disassemble, disassemble all junk), crafting and upgrading, cyberware, character and perks, quests, journal, codex and shards, tarot, map, stash, load game, the EquipmentEx wardrobe, trading (vendor visits open in the VR menu) and all VR settings pages. Every text is in all 19 game languages.
- Touch the world's screens with your index fingertip: elevators, door panels, drop points, computers, terminals and vending machines, with a click vibration. Mail lists, mail text and browser pages scroll under the finger.
- Physical reload for nearly every gun - 51 weapons: all shotguns (pump, break-action and box magazine, shells carried as items), every rifle, the remaining pistols, the SMGs and the LMGs (the drum held as belt and box). Magazines come out on grip + trigger, a dry gun gets its rounds only from a real rack, and a racked handle throws a case. The support hand can also hold a gun by its seated magazine.
- Dual wielding (2.5): each trigger fires its own gun; tap Y to drop the left gun's magazine and B the right one's, and swing that hand down to bring the magazine back; holding Y is the game's Y (weapon switch, weapon wheel). The left gun has its own recoil and vibration and no camera kick.
- Camera scopes on 2.5: every scope is rendered through the scope camera, the panels are readable and the glass is tinted (the Grad's green canvas included).
- Headset presets: Samsung Galaxy XR (contributed by Mike Huang, PR #106), HTC Vive, and HTC Vive Pro / Pro Eye, with second-eye camera assets for their resolutions. The launcher now offers 19 headsets and 139 resolutions.
- The tactical belt has its own attachment slot, so it no longer needs EquipmentEx.

Fixed
- Crashes on loading a save and on exiting the game under 2.5 (a head-gaze write landed past the player's camera cache).
- A crash while loading a save, in the game's item factory: the tactical belt asked for its attachment again every 2 seconds while the save was still loading.
- Volumetric fog no longer jumps on a still camera, and does not smear on head turns.
- The map button of the VR menu could open the perks or the inventory instead while a grip was held.
- Switching mono mode off live brought the second eye back only after the head turned.

Changed
- Requirements: Cyberpunk 2077 2.5 with the 2.5 releases of the frameworks or newer - RED4ext 1.31.0, Cyber Engine Tweaks 1.38.0, redscript 0.5.32, ArchiveXL 1.28.0, TweakXL 1.12.0, Codeware 1.21.0. An ArchiveXL before 1.28 loads no item factories (items in the hands stay invisible); a redscript before 0.5.32 cannot read the 2.5 script cache. Visible Bullets is no longer required.
- L3 + R3 opens the VR menu (held 0.5 s); the VR settings are its Settings section. F10 or Insert still toggles the settings overlay.
- The VR menu's assets are inside cyberpunkvrport.archive: the port ships one archive again.
- New modules: redscript CyberpunkVRPort_EngineStereo, CyberpunkVRPort_DualWield and CyberpunkVRPort_Menu; CET CyberpunkVRPort_Menu.

Upgrading from 0.1.8
- Update the game to 2.5 and the frameworks to their 2.5 releases first. 0.1.9 does not run on 2.31, and 0.1.8 does not run on 2.5.
- Engine stereo starts on with your existing vrport.ini too, because 0.1.8 never wrote the key. Set xr_engine_stereo=0 to go back to the second-view stereo.
- From a development build: delete archive\pc\mod\vrport_menu_native.archive and archive\pc\mod\vrport_menu_panels.archive.

0.1.8

New
- Asymmetric per-eye projection: each eye renders exactly its headset's lens window, at full pixel density and with square pixels, instead of a symmetric frustum. On by default; STEREO VIEW > "Asymmetric projection" (xr_asym_projection, live). Frustum culling, occlusion, light lists and sun cascades follow each eye's window, and the cascades are fitted to the union of both windows.
- Screen-space effects made correct for the asymmetric windows with shader twins: volumetric fog, screen-space and planar (water) reflections, cone AO, sun contact shadows, auto-exposure, particles that face the eye instead of the screen, and screens/holograms that use the pixel's own view ray instead of the camera's forward axis. The two eyes' SSR, planar reflections, AO and contact shadows are merged as one wide display at each eye's inner edge.
- Per-headset resolution ladders shaped to each headset's measured eye window, every entry at the cost of the one it replaces: Quest 2 / 3 / 3S, Pico 4 / 4 Ultra, Pimax Crystal OG / Light / Super / Ultra Wide, Valve Index, Dream Air, PSVR2, Bigscreen Beyond 2 / 2e, Steam Frame, and HP Reverb G2 on its own ladder. A saved resolution that is no longer in its headset's ladder moves to the nearest-cost entry. New headset: MeganeX superlight 8K, with its own ladder and second-eye camera assets.
- Native NVIDIA DLSS Frame Generation through NGX, using the game's own nvngx_dlssg.dll without Streamline; it is the new default generator. FidelityFX frame interpolation can run without optical flow (the new default, ~1.3-1.5 ms for both eyes). Frame generation takes depth and motion from the TAA, FSR 2, FSR 3, FSR 4 and XeSS nodes, so it no longer depends on DLSS; NVIDIA optical flow falls back to FidelityFX on non-NVIDIA GPUs.
- FSR 3, FSR 3.1/4 and XeSS keep a separate context per eye: each eye no longer accumulates the other eye's history (blur and an IPD-wide ghost).
- Fixed foveated DLSS: the game's DLSS/DLAA quality in the centre, independent peripheral quality, region size and offsets (off by default; region 70% x 65%, -10% vertical offset).
- Fixed peripheral VRS and a hidden-area mask (both off by default), and shared sun shadow cascades for both eyes with a native fallback.
- CAS sharpening, applied before frame generation (strength 0 by default, bypassed automatically with the game's DLAA).
- Per-eye depth is submitted to the OpenXR runtime with each frame (XR_KHR_composition_layer_depth), matched to the frame it belongs to, for better runtime reprojection. Generated frames carry no depth. xr_depth_submit, on by default.
- Physical scope optics: low-magnification scopes are real lenses in the headset instead of the flat ADS overlay; sniper rifles look through a render-to-texture scope camera bound to the weapon; collimator reticles are collimated along the bore; shots leave the sight line so the mark is hit at every range. New CyberpunkVRPort_Optics CET and redscript modules.
- VR cyberware combat: physical mantis blades, gorilla arms, monowire and projectile launcher, with their posing, equipment transitions and launcher aiming, enhanced melee, and free-hand gestures driven by the controllers. The monowire leaves the forearm housing along the game's own route, and the line moves with the body instead of being dragged by running and falling.
- Physical melee throws: hold the left trigger with a throwable melee weapon, squeeze the right grip, throw and open the grip. The knife flies close to a straight line (10-45 m/s from the hand's speed), aimed mostly where you looked just before the throw rather than along the hand's falling release. Aim assistance takes the enemy nearest that gaze (within 20 degrees), otherwise one around the throw or the stroke (15 degrees), and the flight curves on to it as in the flat game. While a throw is armed the holster leaves the right grip alone.
- Physical crouch (on by default, 45 cm depth); the VR camera stays stable across weapon changes.
- Controller haptics: a vibration per shot shaped by weapon class (handgun, rifle/SMG/LMG, shotgun, sniper/precision), melee block and parry, bullet block and deflect, a tick when a hand reaches a tactical-belt element and a snap when a grenade pin comes out. A two-handed grip vibrates both hands. CONTROLS > "Controller vibration" and "Vibration strength" (xr_haptics, xr_haptic_scale).
- Pressing Reload plays the game's own reload: both arms and fingers ease onto its animation and back to the controllers 0.15 s before it ends.
- Grapple and takedown, picking up, dropping, throwing and hiding a body, and finishers with a paired animation hand the body to the animation; roomscale stays as it is. While carrying a body the left arm follows the animation and the right hand keeps aiming.
- Physical turns rotate the native body independently of the VR view.
- Longer car steering travel, and the cabin steering wheel animated over it in more vehicles.
- Hit and kill markers on their own head-locked HUD window.
- Every gameplay player replacer (Aguilar, Theo, Kurt, the android, the netrunner and others) gets the second-eye cameras, as Johnny's replacer already had.
- Stage replay (MAIN replays the second eye's recorded render stages) is available as xr_stage_replay; it is off by default.

Fixed
- Auto-exposure no longer swings when the head turns: it is metered from the environment around the player instead of from the view.
- The sun shadow cascade boundary no longer sweeps across the ground with head turns.
- Popups (phone, dialer, vehicle list, radio, messages, shards, car colour pick) no longer double the picture.
- NPC quest markers stay on their chevron and at the same height in both eyes; the second quest marker on a looted body no longer doubles; the second eye's HUD no longer jumps a frame ahead in head turns.
- The scanner is centred on the gaze and sits at infinity in both eyes. The persistent dot, the scanner panel and head-gaze targeting follow the vertical centre of the asymmetric views.
- Scanner gesture and controls: the ear gesture reads coherent grip poses, scanner navigation waits for the game's Vision state, and a rejected request is released, so movement and weapon switching can no longer stay captured.
- The tutorial popup video sits in its place in both eyes instead of covering the button under it.
- The radio port and the vehicle list open lower, inside the view.
- Screen effects (damage, Edgerunner, Sandevistan and other on-screen effects) keep their look, but no longer move the picture differently in each eye.
- At the new-game mirror (character creation) the second eye no longer flashes solid yellow, green and magenta.
- Missing Take/Equip prompts (for example the suit duffle in q303 and Jackie's ofrenda items): the legacy shot-finding hooks that wrote the VR muzzle into the game's targeting origin are gone.
- Manual reload no longer spends the ammo twice; pressing the game's Reload while a hand is on the slide or a magazine is out no longer causes an endless reload or a crash.
- Grabbing a grenade with a weapon in hand puts the weapon away first instead of leaving the hand stuck in the grip; the holster and the belt no longer react to the same squeeze; the held grenade is no longer drawn over the hand.
- A thrown grenade falls past a ledge or a kerb onto the ground below instead of lying on the air.
- The two-hand grip steers relative to where the left hand was when the grip closed, so the weapon no longer jumps on grab and release; it lets go when the hand is pulled 60 cm off the weapon. New keys xr_two_hand_aim, xr_two_hand_break, xr_two_hand_aim_release_ms.
- A slightly canted pistol can still be racked by the slide.
- Projectiles launch from the muzzle; hitscan shots use the cast ray's own position and direction.
- Periodic GameThread hitches caused by the CET Lua garbage collector (in the city the 1% low went from 23-29 to about 45 FPS).
- A crash when pausing: the second view's UI composition is now held with a reference while the game rebuilds the UI.
- Some launches started with the world drained of colour (grey-silver materials): async compute passes are back on the async queue and the grading lend is back to how it was.
- Frame generation with DLAA and with the game's native TAA.
- VR frame timing: rendered frames are published before frame-generation pacing, selected frame timestamps are kept, head prediction is fitted to real presentations with a bounded horizon, and shared or stale stereo depth is rejected. Shader replacements live exactly as long as the game's original pipeline; a swapchain wait timeout no longer releases an image that was never waited for.
- The LOD threshold is also patched at the engine's two other camera-descriptor builders (xr_fix_lod).
- The second view's G-buffer partition lift applies to VRCAM only; every other view keeps the engine's single partition.
- The first eye's render resolution could stay at 1024x768 instead of the selected one.
- The desktop window shows the whole frame at the render's aspect, on its own monitor and never upscaled; cursor and clicks are mapped through the same crop. Eyes use the runtime's sRGB swapchain format where it exists, otherwise they are decoded correctly.
- The settings panel is carried rigidly by the grip (the wrist swings it, the stick pushes and pulls it), and the FPS overlay no longer draws over it.

Changed
- New installs start with stage replay, the submission chain, deferred Present and game-thread render-queue skipping off, and with shared sun cascades and HUD stereo depth on. Values already in your vrport.ini are kept.
- The first-launch preset no longer touches brightness, gamma or the HDR levels (paper white, maximum monitor brightness, tonemapping midpoint): they are kept as the player's own, like language and audio. The preset's HUD crosshair is off, ray-traced lighting is Ultra and the field-of-view maximum is 100 degrees.
- Weapons: the camera recoil kick is removed and hand recoil is 30% lower (xr_recoil_scale); sniper rifles keep their own fire cadence under the VR semi-auto trigger; the Kappa's seated magazine comes out on the button only. Trigger cadence is tuned and muzzle flashes and tracers are reduced.
- Hand smoothing stays on under frame generation at 1.5x the rate (xr_hand_lerp_framegen_scale; 0 switches it off there as before).
- The tuned VRIK wrist rotations are the new base and read as 0 in the overlay; vrik_calibration.ini version 4 stores offsets, and a version 3 file loads as before.
- Hand-gesture calibration is built in; thumbs-up is right-hand only.
- Interaction and loot panels are head-locked by default (cones 0, interaction distance 2 m, FOV 75); a zero free-look cone is accepted everywhere.
- Every packed asset now ships in one cyberpunkvrport.archive with one ArchiveXL manifest.
- vrcam_cpu_tweaks.ini is reduced to the streaming distances and culling settings.
- Lower port overhead: about 1 ms less render-job CPU per frame in RenderElements and scene passes, and empty HUD windows are no longer drawn (about 0.19 ms less GPU).
- Submission chain, deferred Present and render-queue skipping are ini switches for A/B testing (xr_submit_chain, xr_defer_present, xr_gt_skip_render_queue).
- New modules: CET CyberpunkVRPort_Optics and CyberpunkVRPort_PhysicalCrouch; redscript CyberpunkVRPort_BodyCarry, _Cyberware, _Finisher, _Haptics, _Optics and _PopupVisualState.

Upgrading from 0.1.7
- Delete archive\pc\mod\VRCigarette.archive.xl, archive\pc\mod\vrport_basketball.archive and archive\pc\mod\vrport_mag.archive. Their assets are inside cyberpunkvrport.archive now.
- Requirements are unchanged.

0.1.7

New
- Native VR frame generation with game motion vectors and depth, FidelityFX and NVIDIA optical-flow backends, half-rate pacing, and an in-headset performance overlay.
- Controller shortcuts: hold L3+R3 for one second to toggle the VR overlay, or L3+left Grip for half a second to activate iconic cyberware in gameplay.
- More Occluders (Scripted v0.3) is a separate requirement downloaded from its author's Nexus page; its file is not bundled.
- Native VR HUD panels with per-element controls, configurable free-look cones, separate interaction/dialogue and loot panels, and head-following scanner, CCTV, Basilisk and sniper HUDs. HUDitor is no longer required or bundled.
- Controller-operated VR settings overlay with pointing, scrolling, grip dragging, placement controls, game actions, and dedicated Framegen, HUD, driving and bindings pages.
- Native roomscale movement and paired camera/body poses, HMD-aligned bending, anatomical shoulder reach, improved foot contact and hand tracking, and hybrid HMD/controller body rotation.
- Gesture-driven swimming with stroke-speed-dependent propulsion and water-aware avatar posture; grip-based ladder climbing with authored hand and finger poses.
- Third-person and external-camera stereo support, HMD-driven surveillance cameras, and camera-aimed Basilisk steering and cannon targeting.
- Tactical belt with magazine and grenade props, physical grenade handling, male/female assets and restored startup clothing.
- Steam Frame headset preset and native controller bindings; HP Reverb G2 uses the Pico 4 resolution ladder.
- Tutorial player replacer support.

Fixed
- Lamp light beams no longer follow head turns in VRCAM. MAIN fog sharing uses the native temporal reprojection path with its matching source-camera matrix instead of replacing the current-eye integration volume.
- Frame generation accepts ray-tracing motion-vector formats. Switching RT off no longer leaves VRCAM using stale high-feature flags and collapsing to a few FPS.
- Local lights receive MAIN's authored sky radiance before VRCAM CPU preparation. Underwater effects and warm colour grading now reach the second eye correctly.
- Distant-background flicker, cascade shadow mismatches after range/resolution changes, and local flashlight-shadow trails. Both eyes keep native cascade draws and clears; local-shadow reuse defaults to 0.
- Main-menu render initialization, repeated save loads, unavailable terrain buffers, retained depth/RTV resources, weapon-switch rig rebinding, and native world-UI cursor handling.
- Story camera tracking, scene turning and VRIK suspension; moving takeover cameras, camera transitions, sniper head aiming, and the camera objective that requires finding Reed.
- World-marker stereo projection and scaling, native subtitle size/cropping, phone and scanner panel updates, and dedicated story HUD layouts.
- Photo Mode image dimensions and memory growth, plus save-preview screenshots. Photo readback hooks no longer interfere with the game's world-widget picker.
- Keypad cursor speed and continued input while looking away, VR overlay reopening/scrolling, cyberware melee laser visibility and cyberware control routing.
- Steering response and full-lock recovery, seated avatar stability, Combat reload/turn controls, swimming acceleration and duplicate pitch.
- Launcher visibility, focus, cursor release, Unicode window title and close handling.
- Guard against zero VRS tile dimensions on unsupported hardware, addressing the reported AMD integer divide-by-zero path. No physical AMD validation was performed here.

Changed
- First launch merges the complete VR graphics, input, HUD and comfort preset while preserving language, audio, difficulty, telemetry, cloud saves and gallery favorites. Backups and atomic installation protect the original file.
- Removed repeated settings replacement and the old cascade SettingsGuard. Native cascade quality controls remain available.
- Reflex defaults to 0 and show_launcher defaults to 1; saved user overrides remain respected.
- Reduced idle HUD, overlay, belt and Lua work, batched render-state reads, and improved resource/fence ownership. Expensive diagnostics remain opt-in.
- Optional analog stick movement supplements the existing fixed-speed mode.
- Single-pass renderer research remains opt-in development code, not the release stereo path.

0.1.6

New
- The second view builds its own frame instead of being handed the other eye's bytes: the engine's own environment-override pass is RUN for it, its composition state is lent so the pass that draws the scanner outline executes for it at all, and the finished frame is taken at the node epilogue from the engine's own acquire barrier rather than mid-chain.
- The scanner's green tint is in the second eye. It had been credited to three different mechanisms; it is the environment pass alone, with the composition lend off and the LUT lend absent from the build.
- Braindances are stereo. One base, one head sample and one pose label serve both eyes, the eye separation goes where the picture is actually rendered from, and the scene's own field of view arrives from the first frame instead of being learned from a lucky match 54 times out of 1801.
- Cameras you take over are driven properly, the AV turret included -- its camera never reaches the hook this port classifies cameras at, so the lens is identified through the entity the script names and the pair is driven through the located buffer. Both eyes sit at the lens, the head composes onto its aim, and the mission that needs a different viewpoint has three sliders for it.
- The game's own bindings work in menus and in braindances: none of the port's remaps, masks or gestures apply there, so nothing of ours can eat a button a menu needs.
- B closes the phone, the radio port and the vehicle list with a weapon in hand. All three are overlays rather than menus, which is why they used to be impossible to close with a gun out.
- The UI is fitted to the square VR view: the phone's contact list and messenger, the vehicle summon panel, the radio, the subtitles, the dialogue choice list and the tutorial and welcome popups are centred and scaled.
- The loot window has its own module: the plate with the item name, the count and the take button at 0.70, and the detailed description that hung off the right edge centred above it.
- Johnny Silverhand's replacer body carries the 62 stereo camera components and the two held-object slots, so the second eye exists and the physical reload works while playing him.
- A physical two-handed hold and a resting hand: with a weapon out the empty hand relaxes, and bringing it to the weapon offers the support grip, with a captured hold per weapon.
- The braindance notification plate ships as its own CET module, because the slot it needs is declared in a HUD asset the port does not ship.
- The D3D12 debug layer's message queue is drained into the port log -- reads only, and inert unless the layer is forced on for the executable from outside the process. It is the only instrument that has ever named a fault here.

Fixed
- Indoors, every light source stopped reaching any surface in the VR view while emissive, sky and ambient carried on: the second view was handed the other eye's near and far, and that steers the clustered light grid, so every pixel read a bin nobody had filled. It keeps its own depth range now.
- The white second eye, the hang on ESC in a braindance and the missing braindance colour grade were one habit -- anything that was not the second eye was called "MAIN", the flat desktop window and every reflection-probe face included. Views are identified by their virtual-camera name hash now.
- The ESC hang itself: the GPU wait waited on the last signal of every queue it had ever seen, from a table that was never pruned, so a queue the pause menu stops feeding left an unsatisfiable wait and the device was removed.
- The second view was whitened by the exposure mirror, whose copy carries a field the two sides were measured to differ by 2880x in. It ships off.
- Our swapchain images were returned to the runtime in a state it does not expect: 2689 debug-layer errors in a minute, now zero.
- DEVICE_REMOVED for an invalid call: the finished-frame snapshot inherited a TYPELESS format and the blit builds its view from the source format. The snapshot is typed.
- Two crashes inside the composition element walk, both on an element with no owner in this view; such an element now contributes no draw keys.
- The camera classifier dropped 4.3 camera writes a second by re-validating MAIN's latch against a scene camera that is legitimately elsewhere.
- Both eyes juddered in every braindance -- with the replay paused, and invisibly on the flat monitor -- because the two eyes were composed onto different bases.
- Frames were submitted against a pose their pixels were never drawn from: the ring the submit path reads was still being filled by a site whose value was no longer written.
- The stereo pair sat 32 mm apart instead of 64. Both halves of the separation were written at a component, and only one of those components reaches a picture.
- At the AV turret the second eye stayed on the player's head with nothing but an eye separation added.
- Closing an overlay could eject your magazine, because the button that closes it is the one the physical reload drops the magazine with.
- The per-weapon hand-filter speeds were lost when the render half was rolled back: the file they live in was misfiled as render.
- The trampoline's pointer filter stayed disarmed for the whole of a surveillance takeover, on a site that runs some 10 200 times a second.
- The CET module re-resolved the same game handles every frame -- five name lookups, three scriptable systems, the blackboard defs, the player's camera component, the scene interface -- and walked every ink layer ten times a second to find one container.

Changed
- The environment pass ships as the variant that ERASES NOTHING: it walks the same list and calls the same per-entry apply, because removing an element from a shared list on a second thread is the half with a named hazard.
- Detour_DrawComposition is deleted rather than switched off. It served a mode that is off, so its only remaining effect was an extra call to an accessor this tree records as impure.
- Defaults are taken from the configuration that was actually played, since an existing vrport.ini overwrites them at startup: the scanner's slots go neutral, the hand filter's rifle and shotgun speeds become 25 and 20, and the head offsets and the menu field of view are the ones this port is tested with. Seating and vehicle head offsets are deliberately not baked -- those are personal.
- The viewpoint offset for the AV turret ships tuned and keyed by what was taken over, so a surveillance camera on a wall is unaffected.
- Twenty-six log lines that repeat on ordinary paths moved behind the launcher's DEBUG box; "MAIN camera is now" alone printed 50 975 lines in one session. Install lines, their failures and the once-per-session name calibration stay visible, because a hook that failed must not look like one that worked.
- Three probes whose questions are answered are deleted: the vehicle-camera write census, the indirect-argument probe and the grading test lever.
- The package enumerates the archive folder instead of naming three files, which is why one archive was in the repo, in the game, and in no tester's package.
- The README describes what the port does now, including the B rule, and no longer carries the limitation that B cannot close the phone with a weapon drawn.

0.1.5

New
- Wrist readout: a live display sewn into the player's own left forearm -- health, ammo, damage and the scanner's readouts on a strip of the arm's real skin, so it bends and turns with the wrist instead of riding a flat plate. On the male and the female player, each cut from their own forearm with their own bind pose and weights.
- Surveillance cameras are now stereo. Taking one over used to switch the main view while the second eye stayed behind on the player; now both eyes sit at the lens, share its aim and its field of view, and the avatar's IK is suspended exactly as it is in a cutscene.
- First person is held: the perspective toggle does nothing and a car entered in third person is put back, both through the game's own restriction and event rather than a hook.
- The scanner's HUD can be dragged and scaled. HUDitor cannot do it -- its movable set is a fixed list of named controllers and the scanner is not one of them -- so the port ships its own editor and its own input file.

Fixed
- The frame rate collapsed near a surveillance camera with a weapon drawn, 60-70 down to 20. Those cameras cast rays continuously from several worker threads, and every one of them was paying three kernel calls to be recognised as somebody else's. The ownership test is now free: no VirtualQuery anywhere on the ray path.
- The view held a frame while a car turned, which read as a twitch on every corner. 4-12% of rendered frames shared an aim epoch with the previous one and wrote its orientation back -- correct for the head, which had not moved, and stale for the world, which had.
- The avatar jittered while seated in a vehicle: the solve was handed a yaw-only body frame, which is exact on foot and wrong by however far the car had pitched and rolled.
- The second eye borrowed the other eye's frame label, and borrowed its whole image whenever none of its own was paired to the current frame -- a viewpoint one IPD away, in one eye. It now carries its own label and, failing that, its own most recent picture.
- Computers and terminals took the camera away from the head, so the view stopped turning in one eye while the other kept looking around. The screen still opens, takes input and closes; only the one call that hands the camera over is skipped.
- Device screens could not be scrolled at all: three gestures were eating the axis the game reads a message list with. It is handed back while a screen is open.
- Seated in a car, a dialogue line could not be confirmed by anything -- confirming is X, and X is the exit there. A does it now, and the handbrake it also carries keeps working.
- The aim laser's label in the overlay was spelt "lasewr".

Changed
- The scanner is a TOGGLE rather than a hold: squeeze at the ear to open, squeeze again to close, hand free in between.
- The quickhack list moved off the face buttons onto the left stick, pushed to the stop, with X as a plain apply. Reaching across X and Y is the very thing a one-hand scanner exists to avoid.
- The D-pad chord fires at a full push like every other gesture in the port, not at half.
- The shadow cascades are now checked on every launch instead of installed once. They are shared between the two views, so a value drifting off the shipped one replaces UserSettings.json whole -- everything else in that file stays the player's after the first launch, as before. One backup is kept.
- Binding lists in the overlay and the README brought up to date.

0.0.9
- Restructured the code into feature-module folders (src/dxgi/{core, openxr, camera, render, overlay, hooks, aer_v2}, src/common, src/red4ext_plugin/{vrik, weapon}) with per-module CMake include roots.
- Split the 7209-line openxr_manager.cpp into a 1676-line core plus openxr_frameloop, openxr_present, openxr_capture, openxr_calibration and openxr_aer_v2_worker. No behaviour change.
- Restored mono-depth capture and AER stereo (dormant AER thread, per-eye toggle, late IPD shift) with steadier fence/swapchain waits.
- SteamVR: mono submit now runs on the dedicated thread (like AER) instead of inline on the game's Present thread, so SteamVR frame pacing no longer freezes or lags the game. VDXR keeps the inline path.
- AER submit now defaults off.
- D-pad emulation moved to the left stick click: hold the left stick click (L3) and push the right stick to send D-pad Up/Down/Left/Right. Previously it was Right Grip + right stick. L3 still works as sprint when no D-pad direction is used.
- VR HUD: the "Phone" placement region is now labelled "HP Bar".
- Camera shake frozen at the rig (Aim_JNT swing-only, snap-safe); sprint dive/snap double removed; melee swings tuned; holster zone margin tweak.
- VRIK: snap-turn arm fixes; arms-only IK in vehicles.
- Branched from 0.0.8; does not include iPowerTech's PR #7 shadowmap fix (kept on the local pr-7 branch).
- Known issue: RivaTuner (RTSS) / MSI Afterburner OSD can crash the game in VR (its DXGI Present hook conflicts under the SteamVR compositor). Disable it, and other overlay injectors (NVIDIA overlay, OBS OpenXR mirror, Razer Chroma), before launching in VR.

0.0.8
- Physical body rotation is now an explicit toggle, off by default (F10 -> VRIK). Off restores the classic stick/snap-turn heading; vehicles unaffected. Contributed by iPowerTech (PR #6).
- Fixed canted-display projection: a proper non-square canted-lens projection matrix for HMDs with canted panels (Valve Index, Pimax), superseding the 0.0.7.5 square workaround. Tested on PICO 4, Quest 3, Pimax Crystal OG. (iPowerTech)
- Added a pre-launch device list to pick the HMD and native or scaled per-eye resolution. (iPowerTech)
- Added the Crosshair mod (CET): hides the flat 2D crosshair while VR weapon-aim is active. (iPowerTech)

0.0.7.5
- Physical body rotation and a dedicated vehicle camera handler. (iPowerTech)
- DPAD emulation: Right Grip + right thumbstick direction -> D-pad Up/Down/Left/Right. (iPowerTech)
- Body rotation while aiming; the first-person hand/barrel point is no longer drawn. (iPowerTech)
- Crosshair hidden while aiming a weapon, plus laser-pointer handling. (iPowerTech)
- GetVRWeaponAim script function exposing the weapon-aim state to CET/redscript. (iPowerTech)
- Fixed the 3D world not being visible / artifacts on canted-display HMDs by forcing a square render resolution again.
- Stopped building and shipping the experimental d3d12.dll proxy.
- CMake now enables the C language so the Ninja generator builds the MinHook C sources.

0.0.7
- AER V2 reprojection: synthesises the second eye and intermediate frames from the mono output using NVIDIA Optical Flow plus a depth-aware warp (unified producer, late IPD). Falls back to a D3D12-compute optical-flow path without CUDA/NvOF.
- Depth capture/resolve and colour-blit passes feeding the reprojection.
- CAS sharpening pass with overlay-tunable strength/mix.
- DLSS / NGX hook and DLSS matrix handling.
- Runtime FOV correction plus world-scale, IPD-scale and stereo-scale controls.
- Pose pair-locking (anti-tear) and motion prediction.
- Mono/AER submit safety flags (cross-queue wait, depth-capture gating) so the game no longer hangs on menus or save/load.
- Full-body VRIK avatar: body under the HMD, distributed spine, arm-length calibration, leg IK, real-life squat, camera-to-head bake on calibration, 1:1 controller hands.
- Decoupled VR weapon aim (bullet from the barrel) with an optional barrel crosshair dot that scales with scope zoom.
- VR motion melee: a real controller swing fires the game's native melee along the blade.
- Weapon-Up: keeps a drawn melee weapon out of the auto-lower/auto-unequip path.
- No-Anims: neutralises the VR-fighting animations while keeping ADS, recoil and reload intact.
- Hand-to-holster equip/unequip on a grip squeeze: immersive (by visual holster) or simple slot mode.
- VR controllers merged into XInput gamepad 0. Sprint = left stick fully forward; crouch = right stick fully down; snap or smooth turn; locomotion source Game/HMD/Left/Right hand; optional HMD-only pitch.
- World-map head-lock so the map no longer swims while open.
- F10 overlay with tabbed, live, persisted settings (vrport.ini); quiet-by-default logging with a verbose toggle.

