 var data =
{
    "catchPhrase": "Made for speed and elegance.",
    "background": "images/e.jpg",
    "title": "Aurora 2D",
    "description": "Replaces the value corresponding to this entry with the specified value (optional operation). This implementation simply throws UnsupportedOperationException, as this class implements an immutable map entry.Replaces the value corresponding to this entry with the specified value (optional operation). This implementation simply throws UnsupportedOperationException, as this class implements an immutable map entry.Replaces the value corresponding to this entry with the specified value (optional operation).",
    "classes": [
        {
            "title": "A2DAbstract (SAMPLE)",
            "dataType": "class (Template)",
            "rawHeader" : "#ifndef __A2DABSTRACT_H__$#define __A2DABSTRACT_H__$$//+-----------------------------------------------------------------------------$//$// Abstract Class:$// A2DABSTRACT$//$// Synopsis:$// Differentiates which of the two possible arcs could match the given arc$// parameters.$//$//------------------------------------------------------------------------------$$////////////////////////////////////////////////////////////////////////////////$// INCLUDE$////////////////////////////////////////////////////////////////////////////////$$#include \"stdafx.h\"$$////////////////////////////////////////////////////////////////////////////////$// FORWARD DECLARATIONS$////////////////////////////////////////////////////////////////////////////////$$class  A2D;class   A2DAbstract;class   A2DRenderable;class A2DAbstractComponent;class  A2DCamera;struct    A2DCameraProperties;struct  A2DRenderData;class A2DMatrixFactory;class  A2DDXLink;class A2DMatrixFactory;class  A2DModelFactory;class   A2DRootPane;struct  A2DWindowProperties;class   A2DWindow;class A2DImagePanel;$$////////////////////////////////////////////////////////////////////////////////$// DEFINE$////////////////////////////////////////////////////////////////////////////////$$#define A2DABSTRACT_LL(str1, str2) str1 str2$$////////////////////////////////////////////////////////////////////////////////$// DECLARATION$////////////////////////////////////////////////////////////////////////////////$$class A2DAbstract{public:$ $ // Constructor$ A2DAbstract(); $ // Deconstructor$ ~A2DAbstract();$ // Variables$ // [NONE]$$ // Accessors$ // [NONE]$$ // Mutators$ // [NONE]$$ // Builders$ // [NONE]$$ // Factory$ // [NONE]$$ // Additional$ // [NONE]$$protected:$$ // Pure Virtual$ virtual HRESULT Initialize() = 0; // Initialize $ virtual void Deinitialize() = 0; // Shutdown $$ // Virtual $ virtual LPCWSTR GetClass(); // Class type $ virtual bool operator==(A2DAbstract * xAbstract); // Class type $ virtual LPCWSTR ToString(); // Class type $$$ // Implementations$ // [NONE]};$#endif",
            "rawCpp" : "#include \"stdafx.h\"$ #include \"../../Include/A2DAbstract.h\"$$ A2DAbstract::A2DAbstract(){} A2DAbstract::~A2DAbstract(){} LPCWSTR A2DAbstract::GetClass() { return L\"A2DAbstract\"; } LPCWSTR A2DAbstract::ToString() { return L\"A2DAbstract\"; } bool A2DAbstract::operator==(A2DAbstract * xAbstract) { return this == xAbstract; } ",
            "background": "images/a.jpg",
            "description": "A2DAbstract helps create Object Oriented Programming (OOP). All 'Objects' in A2D will extend this class. It is required to override the pure-virtual functions. In doing so, we are able to better develop an algorithms that will help us compare objects, retrieve classnames, convert to LPSCSTR, and more...",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code", // code || normal
                        "title": "public bool operator==(A2DAbstract xAbstract);",
                        "icons": ["methodVirtual"] // method[methodType]
                    },
                    "sections": [
                        {
                            "type": "params", //normal //params //code //return //warning
                            "data": "Replaces the value corresponding to this entry with the specified value (optional operation). This implementation simply throws UnsupportedOperationException, as this class implements an immutable map entry.Replaces the value corresponding to this entry with the specified value (optional operation). This implementation simply throws UnsupportedOperationException, as this class implements an immutable map entry.Replaces the value corresponding to this entry with the specified value (optional operation). This implementation simply throws UnsupportedOperationException, as this class implements an immutable map entry.",
                            "args": [
                                {
                                    "title": " title",
                                    "description": "yolo description"
                                },
                                {
                                    "title": " title",
                                    "description": "yolo description"
                                }  
                            ]
                        },
                        {
                            "type": "code", // The code below will be formatted automatically. But I wrote it. So its not the best. LEGEND:: $ == newline
                            "data": "#ifndef __A2DABSTRACTCOMPONENT_H__$#define __A2DABSTRACTCOMPONENT_H__$$//+-----------------------------------------------------------------------------$//$// Abstract Class:$// A2DABSTRACTCOMPONENT$//$// Synopsis:$// Differentiates which of the two possible arcs could match the given arc$// parameters.$//$//------------------------------------------------------------------------------$$////////////////////////////////////////////////////////////////////////////////$// INCLUDE$////////////////////////////////////////////////////////////////////////////////$$#include \"stdafx.h\"$$#include \"A2DRenderable.h\"$$////////////////////////////////////////////////////////////////////////////////$// FORWARD DECLARATIONS$////////////////////////////////////////////////////////////////////////////////$$class A2D;$class A2DAbstract;$class A2DRenderable;$class A2DAbstractComponent;$class A2DCamera;$struct A2DCameraProperties;$struct A2DRenderData;$class A2DMatrixFactory;$class A2DDXLink;$class A2DMatrixFactory;$class A2DModelFactory;$class A2DRootPane;$struct A2DWindowProperties;$class A2DWindow;$class A2DImagePanel;$$////////////////////////////////////////////////////////////////////////////////$// DEFINE$////////////////////////////////////////////////////////////////////////////////$$#define A2DABSTRACTCOMPONENT_LL(str1, str2) str1 str2$$////////////////////////////////////////////////////////////////////////////////$// DECLARATION$////////////////////////////////////////////////////////////////////////////////$$class A2DAbstractComponent : public A2DRenderable${public:$$// Constructor$A2DAbstractComponent();$$// Deconstructor$~A2DAbstractComponent();$$protected:$$// Variables$A2DAbstractComponent ** aComponents;$int aComponentsIndex = 0;$int aComponentsLength = 0;$$// Accessors$// [NONE]$$// Mutators$// [NONE]$$// Builders$A2DAbstractComponent ** CreateAmmoritizedComponentArray();$$// Factory$// [NONE]$/*$public:$$// Additional$void Add(A2DAbstractComponent * xAbstractComponent);$$private:$$// Additional$void RemoveComponent(A2DAbstractComponent * xAbstractComponent);$void AddComponent(A2DAbstractComponent * xAbstractComponent);$$protected:$$// Pure Virtual$virtual void RenderComponent(A2DRenderData * xRenderData) = 0;$virtual void RenderComponentBorder(A2DRenderData * xRenderData) = 0;$$// Virtual$virtual LRESULT WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam);$virtual void RenderChildren(A2DRenderData * xRenderData) final;$virtual HRESULT CreateChildrenResources(A2DRenderData * xRenderData) final;$virtual HRESULT InitializeChildren() final;$virtual void DeinitializeChildren() final;$virtual void                  DestroyChildrenResources() final;$*/$public:$$// Virtual$virtual void Render(A2DRenderData * xRenderData) final;$virtual HRESULT CreateResources(A2DRenderData * xRenderData) final;$virtual void DestroyResources() final;$$public:$$// Implementation$// [A2DRENDERABLE]$virtual HRESULT CreateComponentResources(A2DRenderData * xRenderData) = 0;$virtual void DestroyComponentResources() = 0;$virtual void Update(A2DRenderData * xRenderData) final;$$public:$$// Implementation$// [A2DABSTRACT]$virtual HRESULT Initialize();$virtual void Deinitialize();$virtual LPCWSTR GetClass();$virtual LPCWSTR ToString();$virtual bool operator==(A2DAbstract * xAbstract);$};$$#endif"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " title",
                                    "description": "yolo description"
                                },
                                {
                                    "title": " title",
                                    "description": "yolo description"
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "title": "A2DAbstract",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": "This class is the root class of Aurora 2D. Contains: Initialize, Deinitialize, GetClass, IsEquals (==), and ToString methods. Based on the Java Object Class.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstract(); ",
                        "icons": [
                                "methodConstructor",
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Constructor that initializes an A2DAbstract object. Allocates memory in the heap to be assigned to an A2DAbstract object."
                        },
                        {
                            "type": "code",
                            "data": " A2dAbstract object;//creates the A2DAbstract object"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual HRESULT Initialize() ",
                        "icons": [
                                "methodConstructor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Allocates memory in the heap to be assigned to an A2DAbstract object and returns whether it was successful. This is a pure virtual funciton in the A2DAbstract class, so note that it is generally necessary to override this method in all subclasses."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$object.Initialize();//Initializes an A2DAbstract object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " ~A2DAbstract() ",
                        "icons": [
                                "methodDeconstructor",
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Destructor that Deinitializes an A2DAbstract object. Deallocates memory in the heap currently assigned to an A2DAbstract object."
                        },
                        {
                            "type": "code",
                            "data": "// Destructor ~A2DAbsract is called before control returns from main()$//OR$A2DAbstract aobject;$aobject->A2DAbstract::~A2DAbstract()"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "virtual void Deinitialize() ",
                        "icons": [
                                "methodDeconstructor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Deallocates memory assigned to the previously created object and unassigns all pointers to the object. This is a pure virtual funciton in the A2DAbstract class, so note that it is generally necessary to override this method in all subclasses."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$object.Initialize();$object.Deinitialize();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "bool A2DAbstract::operator==(A2DAbstract * xAbstract)",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xAbstract",
                                    "description": "an A2DAbsract pointer"
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "The equals method for class Object implements the most discriminating possible equivalence relation on objects; that is, for any non-null reference values `x` and `y`, this method returns `true` if and only if `x` and `y` refer to the same object (`x == y` has the value `true`). Note that it is generally necessary to override the `hashCode` method whenever this method is overridden, so as to maintain the general contract for the hashCode method,which states that equal objects must have equal hash codes."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$A2DAbstract object2 = object;$ bool check = object==object2; //check = true"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " bool ",
                                    "description": "`true` if this object is the same as the obj argument; `false` otherwise."
                                },
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DAbsract::ToString()",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": ""
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a string representation of the A2DAbsract instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DAbsract` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$cout << \"Class type : \" << object.ToString() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR ",
                                    "description": "a wide string representation of the A2D object."
                                },
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DAbsract::GetClass()",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DAbstract` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$cout << \"Class type : \" << object.GetClass() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR",
                                    "description": "Retruns information in the form of a wide string on what class is being implemented."
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "title": "A2DRenderable",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": "This class initializes and sets up a rendering environment for A2D Rendering. Creates the necessary sources and other setup to begin rendering. Contains: Initialize, Deinitialize, CreateResources, DestroyResources, GetClass, IsEquals (==), and ToString methods. Based on the Java Object Class.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DRenderable() ",
                        "icons": [
                                "methodConstructor",
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Constructor that initializes an A2DRenderable object. Allocates memory in the heap to be assigned to an A2DRenderable object."
                        },
                        {
                            "type": "code",
                            "data": " A2DRenderable object;//creates the A2DRenderable object"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual HRESULT CreateResources(A2DRenderData * xRenderData) ",
                        "icons": [
                                "methodConstructor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xRenderData",
                                    "description": " An A2DRenderData object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Creates the necessary resources for an A2DRenderable object. A purely virtual method in the `A2DRenderable` class, must be overridden by every subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$object.CreateResources(xRenderData1);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. A2DRenderablereturns `NULL` "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "virtual void DestroyResources() = 0 ",
                        "icons": [
                                "methodDeconstructor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Destroys the prevoiusly created resources of an A2DRenderable object. A purely virtual method in the `A2DRenderable` class, must be overridden by every subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$object.CreateResources(xRenderData1);$object.DestroyResources();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                 {
                    "header": {
                        "type": "code",
                        "title": "virtual void Update() = 0;",
                        "icons": [
                                "methodAccessor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Updates the prevoiusly created resources of an A2DRenderable object. A purely virtual method in the `A2DRenderable` class, must be overridden by every subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$object.CreateResources(xRenderData1);$object.Update();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " HRESULT Initialize()",
                        "icons": [
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Initializes whatever buffers, handles, pointers or other resources that the A2DRenderable object requires and returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$object.Initialize();//Initializes an A2DRenderable object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. A2DRenderable returns `NULL`"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "virtual void Deinitialize() ",
                        "icons": [
                                "methodDeconstructor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Deallocates memory assigned to the previously created object and unassigns all buffers, handles, pointers, and other resources assigned to the object. This is a pure virtual funciton in the A2DAbstract class, so note that it is generally necessary to override this method in all subclasses."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$object.Initialize();$object.Deinitialize();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "bool A2DRenderable::operator==(A2DAbstract * xAbstract)",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xAbstract",
                                    "description": "an A2DAbsract pointer"
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "The equals method for class Object implements the most discriminating possible equivalence relation on objects; that is, for any non-null reference values `x` and `y`, this method returns `true` if and only if `x` and `y` refer to the same object (`x == y` has the value `true`). Note that it is generally necessary to override the `hashCode` method whenever this method is overridden, so as to maintain the general contract for the hashCode method,which states that equal objects must have equal hash codes."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$A2DRenderable object2;$ bool check = object2==object; //check = false"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " bool ",
                                    "description": "`true` if this object is the same as the obj argument; `false` otherwise."
                                },
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DRenderable::ToString()",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": ""
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a string representation of the A2DRenderable instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DRenderable` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$cout << \"Class type : \" << object.ToString() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR ",
                                    "description": "a wide string representation of the A2D object."
                                },
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DRenderable::GetClass()",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DRenderable` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderable object;$cout << \"Class type : \" << object.GetClass() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR",
                                    "description": "Retruns information in the form of a wide string on what class is being implemented."
                                }
                            ]
                        }
                    ]
                }
            ]
        },
        {
            "title": "A2DRenderData",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": "This class creates and intializes the necessary matrices, buffers, and window properties to begin rendering. Contains: Initialize, Deinitialize, GetClass, IsEquals (==), and ToString methods. Based on the Java Object Class.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DRenderData() ",
                        "icons": [
                                "methodConstructor",
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Constructor that initializes an A2DRenderData object. Allocates memory in the heap to be assigned to an A2DRenderData object. Creates and initializes these matrices: `aViewMatrix(NULL)`, `aWorldMatrix(NULL)`, `aOrthogonalMatrix(NULL)`, and `aProjectionMatrix(NULL)` all with null parameters. Initializes these buffers and properties: `aCameraProps(NULL)`, `aBackBuffer(NULL)`, `aWindowProps(NULL)`, and for all matrices, buffers, and props `NULL` parameters are passed to indicate an initial and basic instance."
                        },
                        {
                            "type": "code",
                            "data": " A2DRenderData object;//creates the A2DRenderData object"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " A2DRenderData(A2DRenderData * xRenderData) ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xRenderData",
                                    "description": " An A2DRenderData object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Constructor that initializes an A2DRenderData object. Allocates memory in the heap to be assigned to an A2DRenderData object. Creates and initializes these matrices: `aViewMatrix(NULL)`, `aWorldMatrix(NULL)`, `aOrthogonalMatrix(NULL)`, and `aProjectionMatrix(NULL)` all with the xRenderData varible (an A2DRenderData pointer) pointing to the matrix in the parameters. Initializes these buffers and properties: `aCameraProps(NULL)`, `aBackBuffer(NULL)`, `aWindowProps(NULL)`, and for all matrices, buffers, and props the xRenderData varible (an A2DRenderData pointer) points to buffer or prop in the parameters. "
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderData object(xRenderData1);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " HRESULT Initialize()",
                        "icons": [
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Initializes whatever buffers, handles, pointers etc that the A2DRenderData object requires and returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderData object;$object.Initialize();//Initializes an A2DRenderData object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. A2DRenderData returns `NULL`"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "virtual void Deinitialize() ",
                        "icons": [
                                "methodDeconstructor",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Deallocates memory assigned to the previously created object and unassigns all buffers, handles, pointers, etc. to the object. This is a pure virtual funciton in the A2DAbstract class, so note that it is generally necessary to override this method in all subclasses."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderData object;$object.Initialize();$object.Deinitialize();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "bool A2DAbstract::operator==(A2DAbstract * xAbstract)",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xAbstract",
                                    "description": "an A2DAbsract pointer"
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "The equals method for class Object implements the most discriminating possible equivalence relation on objects; that is, for any non-null reference values `x` and `y`, this method returns `true` if and only if `x` and `y` refer to the same object (`x == y` has the value `true`). Note that it is generally necessary to override the `hashCode` method whenever this method is overridden, so as to maintain the general contract for the hashCode method,which states that equal objects must have equal hash codes."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsract object;$A2DRenderData object2;$ bool check = object2==object; //check = false"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " bool ",
                                    "description": "`true` if this object is the same as the obj argument; `false` otherwise."
                                },
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DRenderData::ToString()",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": ""
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a string representation of the A2DRenderData instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DRenderData` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderData object;$cout << \"Class type : \" << object.ToString() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR ",
                                    "description": "a wide string representation of the A2D object."
                                },
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DRenderData::GetClass()",
                        "icons": [
                                "methodVirtual",
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DRenderData` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderData object;$cout << \"Class type : \" << object.GetClass() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR",
                                    "description": "Retruns information in the form of a wide string on what class is being implemented."
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    ]
}