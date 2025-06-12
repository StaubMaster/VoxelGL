# VoxelGL
gonna try and make a voxel thing with openGL

# Requirements
lglfw is needen<br/>
on my local machine I specify the direct path because env-paths don't want to work<br/>
on 42 machine I use the '-lglfw' flag<br/>

# Controls
Esc : Closes Program<br/>
W A S D Space ShiftL : Move<br/>
Tab : Inventory/Selection<br/>
Mouse1 (L) : Place<br/>
Mouse2 (R) : Remove<br/>
Mouse4 Mouse5 : Next/Prev in Hotbar<br/>

# Features
## Voxel Place
### Orientation
Voxels can face in any of the 6 Axis Directions (XYZ, Positive Negative)<br/>
in each Axis they can have a Spin in any of the 4 Directions around the Axis<br/>
when Placing a Voxel the Top Axis will try to face away up from the face it was placed on
### Except when it dosen't
some Voxels will Orient (Log) some won't (Grass)
TODO: Have Spin determines by the way the View is facing from the Axis. The Problem is that this would probably need to be hard code which axis to care about, but the Texture Orientation is already hardcoded so it would probybly be fitting.
## Chunk Surrounding
Chunks can be generated at a certain distance and removed at a different distance<br/>
TODO: Save/Load
## Chunk Stage Generation
(currently unstructured)<br/>
When a Chunk is generated it is generated in Stages.
- Allocate
- Fill Basic Voxels
- Request Feature
- Place Feature
Feature will only be generated when all surrounding Chunks have properly Requested their Feature.
BUG: Sometimes a Chunk dosen't include a Structure in the Buffer, placing or removing will update the Buffer and show the Structure properly.

# Extra Features
## PNG Loader
Only works on some Data Blocks, but those seem to be the only ones used.<br/>
No dithering because why would you need that for textures ?<br/>
## Form Controls
some basic Visual Studio C# style Form Controls<br/>
List of Controls:
- Form (the Form itself is a Control)
- Button
- Slot (Inventory)
- Text (Label)
- Toggle (check Box)
List of Forms:
- HotBar
- Inventory
- Debug (dosen't currently do anything)

