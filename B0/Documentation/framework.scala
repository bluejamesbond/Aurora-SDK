Aurora2D : Direct3D Driven Engine

|----------------------|ZOOM OUT UNTIL YOU CAN SEE ALL THESE PLUSES ON THE NEXT LINE WITHIN ONE LINE.-----------------------|

CONVENTIONS
------------------------
http://www.possibility.com/Cpp/CppCodingStandard.html#units

NOTE
------------------------
Sublime Settings:
  - Add to user preferences
    :: "rulers":  [125]

EXPECTED ABSRACTION
------------------------
A2DWindow backWindow;
A2DWindow frontWindow;

// Why use  [ClassName]Factory?
// This is because a instantiating  [ClassName] will only make a basic instance of object
//  [ClassName]Factory will create an  [ClassName] object with more complex behaviors.
// Why use this? This is a save time and better looking code. Framework development :P

// Don't use enums. USE Integers. i.e. 0x222323; This way you can mix styles!

// Format::::
//      [ClassName] +  [Factory] = A2DWindowFactory
//      [Create] +  [Complex] +  [Type without A2D] = CreateComplexWindow
//      [ClassName] +  [Factory] = A2DBoxShadowFactory
//      [Create] +  [Basic] +  [Type without A2D] = CreateBasicBoxShadow

// Integer Constants
//      [A2DConstants]. [Class for which the Factory is working for] +  [Custom Acronym/if needed] +  [Name]
//         i.e. A2DConstants. [AW]_ [WS]_ [BORDERLESS_SHADOW]
//         i.e. A2DConstants. [ABS]_ [BSS]_INSET (A2DBoxShadow_BoxShadowStyle_InsetType)
//              NOTICE:  [AW] and  [WS]. The ending character is the starting character of the other.
//                    :  [ABS] and  [BSS]. The ending 2 characters match the first to of the second.
//                      This is because, it stands for  [ClassName]_ [WhatIsIt+Style]_ [CustomName]
//     Values: 0x034002; // and so on...
//     The only class I see that will be different is A2DColors. This is will not use "Create..." but instead
//     "From". Look at line this to see what I am talking about.

// NOTE: THIS IS FORMATTING IS FOR FRAMEWORK CONSISTENCY. ILL BE DOING THE SAME AS WEL.

A2DWindowFactory.CreateComplexWindow(&backWindow, A2DConstants.AW_WS_BORDERLESS_SHADOW);
A2DWindowFactory.CreateComplexWindow(&frontWindow, A2DConstants.AW_WS_SIMPLE_BORDERLESS);

A2D aurora(&hinstance, &backWindow, &frontWindow, left, top, width, height);
A2DRootPane root = aurora.GetRootPane();

// The Following methods are required in A2DWindow. However, A2D will call it.
// The main will NOT call it.
 1. -> frontWindow.SetRootPane(&root);
 2. -> frontWindow.Initilaize(); // Redirect messages into A2DRootPane that I just passed in.

A2DSimplePane aps();
aps.SetPosition(x, y, width, height);
aps.AddBoxShadow(A2DBoxShadow.CreateComplexBoxShadow(A2DConstants.ABS_BSS_INSET, 1, 2, 30, A2DColors.From(0xEEEEEE));

// Add a child
root.AddChild(aps);

// Start render
aurora.Start(); 

// Shutdown render
aurora.Stop();

EXPECTED ABSTRACTION
------------------------
void main(void)
{
    A2DWindow a = A2DWindowFactory.createWindow(A2DWindowFactory.SHADOWED);
    A2DWindow b = A2DWindowFactory.createWindow(A2DWindowFactory.BLACK_BORDERLESS);
    
    A2D arr = new A2D(a, b);   // Given
    RootPane rp = arr.getRootPane(); // Given
    
    rp.add(new Panel());
    
    b.setRootPanePumping(rp); <---------- BRENT
    
    // A2D 1
    
    A2DWindow a1 = A2DWindowFactory.createWindow(A2DWindowFactory.SHADOWED);    
    Window b1 = A2DWindowFactory.createWindow(A2DWindowFactory.BLACK_BORDERLESS);
    
    A2D arr1 = new A2D(a1, b1);   // Given
    RootPane rp1 = arr.getRootPane();   // Given
    
    b.setRootPanePumping(rp1);          
}

A2DWindow  -> HWND handle, RootPane rpt
                 handle's WndProc -> rpt.pumpInto(data);



Static Classes
=======================================
A2DModelFactory.cpp           [Static]        -> Create Quads and other shapes.
                                 [Functions]
                                    +>  CreateQuad          (
                                                                QuadFrameContainer* xContainer,
                                                                WindowProperties* xWindowProps,
                                                                int xWidth,
                                                                int xHeight,
                                                                int xPositionX,
                                                                int xPositionY);

                                    +>  CleanQuad           (
                                                                QuadFrameContainer* xContainer);
                                    -----------------------------------------------------------------------------------------
A2DWorldMatrixFactory.cpp     [Static]        -> Create World Matrix based on a set of parameters
                                 [Functions] 
                                    -----------------------------------------------------------------------------------------
                                    +>  createMatrix        ();                     // Returns pointer to D3DXMATRIX 
                                                                                    // identity matrix
                                    -----------------------------------------------------------------------------------------
                                    +>  setPosition         (                       // Rotate matrix
                                                                D3DXMATRIX dst      // Destination matrix
                                                                float x,            // Position X (pixels)
                                                                float y,            // Position Y (pixels)
                                                                float z );          // Position Z (pixels)
                                    -----------------------------------------------------------------------------------------
                                    +>  setScale            (                       // Scales matrix
                                                                D3DXMATRIX dst      // Destination matrix
                                                                float scaleX,       // XScaling (ratio)
                                                                float scaleY,       // YScaling (ratio)
                                                                float scaleZ );     // ZScaling (ratio)
                                    -----------------------------------------------------------------------------------------
                                    +>  setRotation         (
                                                                D3DXMATRIX dst      // Destination matrix
                                                                float rotateX,      // Rotate by X (pitch)
                                                                float rotateY,      // Rotate by Y (yaw)
                                                                float rotateZ );    // Rotate by Z (roll)
                                    -----------------------------------------------------------------------------------------
                                    +>  applyMatrix         (                       // Applies transform
                                                                D3DDEVICE device,   // Destination device
                                                                D3DXMATRIX src );   // World Matrix
                                    -----------------------------------------------------------------------------------------
                                 [Optimized Functions] 
                                    O> setPositionWithScale                (...);   // Better than calling position(...) 
                                                                                    // & scale(...)
                                    -----------------------------------------------------------------------------------------
                                    O> setPositionWithRotate               (...);   // Better than calling position(...) 
                                                                                    // & rotate(...)
                                    -----------------------------------------------------------------------------------------
                                    O> setPositionWithScaleAndRotate       (...);   // Better than calling position(...) 
                                                                                    // & scale(...) & rotate(...)
                                    -----------------------------------------------------------------------------------------

Core Classes
=======================================
A2DAbstract                   [Abstract]
                                >> ~A2DAbstract
                                >> virtual protected Initialize
                                >> virtual protected Shutdown
A2DWindow.cpp                 [Class]  [Implements: A2DAbstract]
                                >> ~A2DWindow --> A2DAbstract::~A2DAbstract(); // Contains (2 windows)
                                >> public SetUndecorated(boolean);   // Borderless or not?
                                >> public SetWindowPadding(int);    // Set the 25px window padding this way for shadows.
                                >> public SetDefaultCloseOperation() // This is very last prority
                                >> public SetBoxShadow(boolean); // shadow enabled (curretly only supports one set of borders)
                                >> public SetBorderColor(Color); // Willl be upgraded to use Border class in future
                                >> public SetPosition(int, int);
                                >> public SetSize(int, int);
                                >> public SetPositionAndSize(int, int, int, int); // Dont call either setPositin nor SetSize
                                >> public SetRootPane();
                                >> public SetRootPanePumping(boolean); // checik if RootPane != null. Basically pause/resume
                                >> public SetTitle(String)
A2DRootPane.cpp               [Class]  [Implements: A2DAbstract]        -> Parent of all elements
A2DWindowFactory.cpp         >> public CreateA2DWindow(int constant, int width, int height, String title);
                                >> public MoveWindowTogether(A2DWindow a, A2DWindow b); // Temporary location for method
                                >> public ResizeWindowTogether(A2DWindow a, A2DWindow b); // Temporary location for method
A2DCameraProperties.cpp       [Struct]   [Implements: A2DAbstract]      
                                    ->  Constructor         (   
                                                                float xPositionX,
                                                                float xPositionY,
                                                                float xPositionZ,
                                                                float xRotateX,
                                                                float xRotateY,
                                                                float xRotateZ   );
A2DCamera.cpp                 [Class]
                                    -> A2DCamera             ();                 // Makes a aCameraProps with all zeros
                                    -> GetProperties  [Pointer]  ();                 // Pointer to aCameraProps
                                    -> OnRender                 ();                 // Renders the camera view based on 
                                                                                    // aCameraProps
                                    -> GetViewMatrix            ();                 // Get current matrix settings
A2DProjection.cpp
A2DRenderable                 [Interface]      -> BRENT: To make the simplest rendering object, all you need is to implement this.
                                    -----------------------------------------------------------------------------------------
                                    >> virutal protected CreateResources(...)
                                    >> virutal public Update(...)
                                    >> virutal protected DestroyResources(...) 
                                    -----------------------------------------
A2DAbstractComponent          [Abstract]   [Implements: A2DRenderable]  -> BRENT: From an interface, now we can create a changing window!!!
                                    -----------------------------------------------------------------------------------------
                                    >> protected Render(...)
                                    >> virtual protected WindowEvent(...)
                                    >> virutal protected RenderComponent(...)
                                    >> virtual protected RenderChilden(...)
                                    O> @Override: CreateResources(...)
                                    O> @Override: Update(...)
                                    O> @Override: DestroyResources(...) 
                                    -----------------------------------------------------------------------------------------   
A2DComponent.cpp              [Class]      [Extends: A2DAbstractComponent] -> BRENT: From the abstract class, now panels can contain children!!! See how this works.
                                    ----------------------------------------------------------------------------------------- 
                                    O> @Override: Update(...)
                                    O> @Override: RenderComponent(...)
                                    O> @Override: CreateResources(...)
                                    O> @Override: Render(...)
                                    O> @Override: DestroyResources(...) 
                                    ----------------------------------------------------------------------------------------- 
A2DPanel.cpp                  [Class]      [Extends: A2DComponent] -> BRENT: Now we have complex behaviors!!
                                    -----------------------------------------------------------------------------------------   
                                    >> protected RenderComponentBorder(...)    // These draw outside the component
                                    >> protected RenderComponentBoxShadow(...) // These draw outside the component
                                    >> public SetBorder(int width, Color color, Border type) // All these will be in a struct
                                    >> public AddBoxShadow(BoxShadow type, int x, int y, int radius, int spread, Color color) // All these parameters will be in a struct
                                    >> public SetBorderRadius(int radius)
                                    >> public SetOverflow(Overflow overflow) // <--- Scrollable or not here! Or don't show outside regions
                                    >> public SetGaussianBlur(int radius)   // Blur the parent only if BackGround color has an alpha < 1
                                    >> public SetPosition(TextAlign textalign)
                                    >> public SetPadding(TextAlign textalign)
                                    >> public SetBackground(TextAlign textalign)
                                    O> @Override: RenderChilden(...)
                                    O> @Override: Update(...)
                                    O> @Override: RenderComponent(...)
                                    O> @Override: CreateResources(...)
                                    O> @Override: Render(...)
                                    O> @Override: DestroyResources(...) 
                                    -----------------------------------------------------------------------------------------
A2DLabel.cpp                  [Class]      [Extends: A2DPanel] BRENT: Now we have text!!!!!!
                                    -----------------------------------------------------------------------------------------
                                    >> public SetFont(fontfamily, fontsize) // Parameters will be in a Struct
                                    >> public SetTextAlign(TextAlign textalign)
                                    >> public SetForeground(TextAlign textalign) 
                                    >> public SetTextTranform(TextAlign textalign) 
                                    >> public SetTextOverflow(TextAlign textalign) 
                                    O> @Override: RenderComponentBorder(...)    // These draw outside the component
                                    O> @Override: RenderComponentBoxShadow(...) // These draw outside the component
                                    O> @Override: RenderChilden(...)
                                    O> @Override: Update(...)
                                    O> @Override: RenderComponent(...)
                                    O> @Override: CreateResources(...)
                                    O> @Override: Render(...)
                                    O> @Override: DestroyResources(...) 
                                    -----------------------------------------------------------------------------------------