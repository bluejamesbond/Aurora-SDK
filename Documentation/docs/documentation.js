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
            "background": "images/a.jpg",
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
            "background": "images/b.jpg",
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
        },
        {
            "title": "A2DAbstractComponent",
            "background": "images/h.jpg",
            "dataType": "class",
            "description": "The base class for all A2DComponents except top-level containers. To use a component that inherits from A2DAbstractComponent, you must place the component in a containment hierarchy whose root is a top-level Aurora2D container. Top-level A2D containers are specialized components that provide a place for other A2D components to paint themselves. Based on the Java JComponent Class.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstractComponent() ",
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
                            "data": "Default Constructor that initializes an A2DAbstractComponent object. Allocates memory in the heap or stack to be assigned to an A2DRenderData object. Creates and initializes the render environment with default parameters: `aOptWidth(0)`, `aOptHeight(0)`, `aOptLeft(0)`, `aOptTop(0)`, `aParentComp(NULL)`, `aGraphics(NULL) {}` all with null parameters."
                        },
                        {
                            "type": "code",
                            "data": " A2DAbstractComponent object;//creates the A2DAbstractComponent object"
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
                        "title": " A2DAbstractComponent* GetParent(); ",
                        "icons": [
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Returns a pointer to the Parent A2DAbstractComponent object, which is the root of the component hierarchy. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$ A2DAbstractComponent object2 = object.GetParent();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DAbstractComponent* ",
                                    "description": " Returns a pointer to the parent component. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " A2DGraphics* GetGraphics(); ",
                        "icons": [
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
                            "data": " Method that returns the A2DGraphics pointer to the protected aGraphics pointer of the A2DAbstractComponent class. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$ A2DGraphics object2 = object.GetGraphics();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DGraphics* ",
                                    "description": " Returns an A2DGrpahics* pointer to the aGraphics object of A2DAbstractComponent"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " float GetOptWidth(); ",
                        "icons": [
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
                            "data": " Method that provides the user with the data of the protected aOptWidth variable wtihin the A2DAbstractComponent class. Returns a float type number to indicate Option Width"
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$ float num2 = object.GetOptWidth()"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " float ",
                                    "description": " Returns a float type number to indicate Option Width. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " float GetOptHeight(); ",
                        "icons": [
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
                            "data": " Method that provides the user with the data of the protected aOptHeight variable wtihin the A2DAbstractComponent class. Returns a float type number to indicate Option Height"
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$ float num2 = object.GetOptHeight()"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " float ",
                                    "description": " Returns a float type number to indicate Option Height. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " float GetOptTop(); ",
                        "icons": [
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
                            "data": " Method that provides the user with the data of the protected aOptTop variable wtihin the A2DAbstractComponent class. Returns a float type number to indicate Option Top. Thus the component's top pixel location will be returned to the user. OptBottom is not necessary because it would be a mirror of OptTop."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$ float num2 = object.GetOptTop()"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " float ",
                                    "description": " Returns a float type number to indicate Option's Topmost location "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " float GetOptLeft(); ",
                        "icons": [
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
                            "data": " Method that provides the user with the data of the protected aOptLeft variable wtihin the A2DAbstractComponent class. Returns a float type number to indicate the left most pixel of the opition in question. No need for OptRight, as that would be a mirror of Left."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$float num2 = object.GetOptLeft()"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " float ",
                                    "description": " Returns a float type number to indicate Option's Leftmost location. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstractComponent** CreateAmmoritizedComponentArray(); ",
                        "icons": [
                                "methodConstructor"
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
                            "data": " Takes the array aChildrenComps of A2DAbstractComponent objects and returns a new array twice as long with the originally contained objects preserved."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DAbstractComponent** arrayobject = object.CreateAmmoritizedComponentArray();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DAbstractComponent** ",
                                    "description": " A pointer of an array of A2DAbstractComponent children"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " A2DGraphics* CreateGraphics(); ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Creates and initializes the A2DGraphics object that is utilized by the A2DAbstractComponent class. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DGraphics object2 = object.CreateGraphics();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DGraphics* ",
                                    "description": " Returns a pointer to an A2DGraphics object resident to the A2DAbstractComponent object "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void Add(A2DAbstractComponent * xAbstractComponent); ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xAbstractComponent ",
                                    "description": " A pointer to an A2DAbstractComponent object to be added "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " A method abstracting the `add` processs for the user. Internally calls AddComponent which doubles the aChildrenComps array, preserving the original children, and adds the desired object into the array of A2DAbstractComponent objects. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DAbstractComponent object2;$A2DAbstractComponent object.add(object2);"
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
                        "title": " void SetParent(A2DAbstractComponent * xComponent); ",
                        "icons": [
                                "methodMutator"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xComponent ",
                                    "description": " An A2DAbstractComponent object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the parent A2DAbstractComponent object of a the A2DAbstractComponent aParentComp protected object to the desired A2DAbstractComponent component object. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DAbstractComponent object2;$A2DAbstractComponent object.SetParent(object2);"
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
                        "title": " void RemoveComponent(A2DAbstractComponent * xAbstractComponent); ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xAbstractComponent ",
                                    "description": " An A2DAbstractComponent object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " NEED TO FIX, FILL IN LATER OR MAKE REMOVE METHOD "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DAbstractComponent object2;$A2DAbstractComponent object.add(object2);$object.RemoveComponent(object2);"
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
                        "title": " void AddComponent(A2DAbstractComponent * xAbstractComponent); ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xAbstractComponent ",
                                    "description": " A pointer to an A2DAbstractComponent object to be added "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " A method abstracting the `add` processs for the user. Internally calls AddComponent which doubles the aChildrenComps array, preserving the original children, and adds the desired object into the array of A2DAbstractComponent objects. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DAbstractComponent object2;$A2DAbstractComponent object.add(object2);"
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
                        "title": " virtual void RenderComponent(A2DRenderData * xRenderData) = 0; ",
                        "icons": [
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
                            "data": "  "
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
                        "title": " virtual void RenderComponentBorder(A2DRenderData * xRenderData) = 0; ",
                        "icons": [
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
                            "data": "  "
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
                        "title": " virtual void SetBounds(float xOptLeft, float xOptTop, float xOptWidth, float xOptHeight); ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xOptLeft ", 
                                    "description": " float value of Leftmost position "
                                    
                                },
                                {
                                    "title": " xOptTop ", 
                                    "description": " float value of Topmost position "
                                    
                                },
                                {
                                    "title": " xOptWidth ", 
                                    "description": " float value of component width "
                                    
                                },
                                {
                                    "title": " xOptHeight ",
                                    "description": " float value of component height"   
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the A2DAbstractComponent objects boundaries. This is done through enumerating the total width of the component, the total height, and the top and leftmost positions. Right and Bottom are not necessary. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent obejct;$object.SetBounds(0,100,200,200);"
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
                        "title": " virtual LRESULT WindowMsg(HWND * xHwnd, UINT * xMessage, WPARAM * xWParam, LPARAM * xLParam); ",
                        "icons": [
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xHwnd",
                                    "description": " A HWND pointer"
                                },
                                {
                                    "title": " xMessage",
                                    "description": " A UINT pointer"
                                },
                                {
                                    "title": " xWParam",
                                    "description": " An WPARAM object pointer"
                                },
                                {
                                    "title": " xLParam",
                                    "description": " An LPARAM object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Method that passes a message to the component's window...passes it all the children based on location(?)"
                        },
                        {
                            "type": "code",
                            "data": "//"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LRESULT ",
                                    "description": " "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void RenderChildren(A2DRenderData * xRenderData); ",
                        "icons": [
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
                            "data": " method that renders all children of the RenderData object passed in. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DRenderData object2;$object.RenderChildren(object2);"
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
                        "title": " virtual HRESULT CreateChildrenResources(A2DRenderData * xRenderData) final; ",
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
                            "data": " Method that creates and initializes the resources for every child component in the A2DAbstractComponent protected data member,  aChildrenComps, through the Renderdata parameter passed in for all of them. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DRenderData object2;$object.CreateChildrenResources(object2);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Infrorms the user whether successful or if it failed."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void DeinitializeChildren() final; ",
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
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Method that Deinitializes every child component in the A2DAbstractComponent protected data member aChildrenComps"
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$object.DeinitializesChildren();"
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
                        "title": " virtual void DestroyChildrenResources() final;",
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
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Destroys the Resources of every child component of the A2DAbstractComponent object. These chidlren components are located in the object's  protected data member aChildrenComps. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$object.DestroyChildrenResources();"
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
                        "title": " virtual HRESULT CreateComponentResources(A2DRenderData * xRenderData) final;",
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
                            "data": " metod that creates a graphical render setup for the passed in A2DRenderData object. If the object is of the parent A2DGraphics type, this is not valid and `failiure` is returned. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DRenderData object2;$object.CreateComponentResources(ojbect2);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Informs the user of success or failiure."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void DestroyComponentResources() final; ",
                        "icons": [
                                "methodDeconstructor",

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
                            "data": " Destroys the specific A2DAbstractComponent object's resources. May be overridden by subclasses for a more specific implementation. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$object.CreateComponentResources();$object.DestroyComponentResources();"
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
                        "title": " virtual void Render(A2DRenderData * xRenderData); ",
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
                                    "title": " xRenderData",
                                    "description": " An A2DRenderData object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Method that renders the component specified, it's children, and it's borders within the A2DAbstractComponent class object's constraints. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DRenderData object2;$object.Render(object2);"
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
                        "title": " virtual HRESULT CreateResources(A2DRenderData * xRenderData) final;",
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
                            "data": " Method called by CreateComponentResources. Fundamental method that actually creates a graphical render setup for the passed in A2DRenderData object. If the object is of the parent A2DGraphics type, this is not valid and `failiure` is returned. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$A2DRenderData object2;$object.CreateComponentResources(ojbect2);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Informs the user of success or failiure."
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
                            "data": "Destroys the prevoiusly created resources of an A2DAbstractComponent object. A purely virtual method in the `A2DAbstractComponent` class, must be overridden by every subclass."
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
                            "data": "Updates the prevoiusly created resources of an A2DAbstractComponent object. A purely virtual method in the `A2DAbstractComponent` class, must be overridden by every subclass."
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
                            "data": "Initializes whatever buffers, handles, pointers etc that the A2DAbstractComponent object requires and returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$object.Initialize();//Initializes an A2DAbstractComponent object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. A2DAbstractComponent returns `NULL`"
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
                        "title": "LPCWSTR A2DAbstractComponent::ToString()",
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
                            "data": "Returns a string representation of the A2DAbstractComponent instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DAbstractComponent` returns a string consisting of the name of the class."
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
                        "title": "LPCWSTR A2DAbstractComponent::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DAbstractComponent` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractComponent object;$cout << \"Class type : \" << object.GetClass() << endl;"
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
            "title": "A2DComponent",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": " An essential class of the Aurora2D library, A2DComponent is the class that allows users to make up different \"components\" or \"sections\" of their desired UI. A single componenent defines that \"section's\" texture, blur, translation, background, position, and size properties. Additional properties may be added by subclasses or more specific implementations. ",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DComponent() ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Default Constructor that initializes an A2DComponent object. Allocates memory in the heap or stack (depending on scope) to be assigned to an A2DComponent object. "
                        },
                        {
                            "type": "code",
                            "data": " A2DComponent object;//creates the A2DComponent object"
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
                        "title": " ~A2DComponent() ",
                        "icons": [
                                "methodDeconstructor"
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
                            "data": "Deallocates memory assigned to the previously created A2DComponent object. Default constructor, will be called by the system even if the user doesn't call it explicitly."
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;//once the program or scope is exited, the object will be destroyed"
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
                        "title": " void SetDoubleBuffered(bool xDoubleBuffer) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": "xDoubleBuffer ",
                                    "description": " bool parameter indicating whether to set DoubleBuffering "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Takes true` or `false` whether the Componenet is set to allow DoubleBuffering or not. DoubleBuffering allows \"preparation\" of two frames beforehand to allow faster and more smooth rendering.  "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$object.SetDoubleBuffered(true);"
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
                        "title": " bool IsDoubleBuffered() ",
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
                            "data": " Returns whether the A2DComponent object has been set to allow DoubleBuffering or not. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$ bool check = obejct.IsDoubleBuffered();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " bool ",
                                    "description": " Returns true or false to indicate whether DoubleBuffering is set."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " LPCWSTR * GetOptBackgroundImage() ",
                        "icons": [
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
                            "data": " Returns to the user the source of the background image used by the reference A2DComponent object through a Long Wide String object indicating the source image's name/information. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$LPCWSTR * object2 = object.GetOptBackgroundImage();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR * ",
                                    "description": " Returns an LPCWSTR pointer to the name of the source image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " int GetOptBackgroundPositionX() ",
                        "icons": [
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
                            "data": " Returns the current background position's x-coordinate (of the specified A2Dcomponenent object) as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int posx = object.GetOptBackgroundPositionX();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " Returns the cartesian x-coordinate of the background image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " int GetOptBackgroundPositionY() ",
                        "icons": [
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
                            "data": " Returns the current background position's y-coordinate (of the specified A2Dcomponenent object) as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int posy = object.GetOptBackgroundPositionY();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " Returns the cartesian y-coordinate of the background image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " int GetOptBackgroundSizeX() ",
                        "icons": [
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
                            "data": " Returns the current background position's size width-wise (distance between the leftmost and rightmost x-coordinates) of the specified A2Dcomponenent object as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int sizex = object.GetOptBackgroundSizeX();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " Returns the cartesian horizontal size of the background image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " int GetOptBackgroundSizeY() ",
                        "icons": [
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
                            "data": " Returns the current background position's size length-wise (distance between the top and bottom y-coordinates) of the specified A2Dcomponenent object as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int sizey = object.GetOptBackgroundSizeY();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " Returns the cartesian vertical size of the background image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " int GetOptBackgroundColor() ",
                        "icons": [
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
                            "data": " Returns the current background css reference color of the specified A2Dcomponenent object as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int col = object.GetOptBackgroundColor();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " Returns the css reference of the color of the background image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " int GetOptBackgroundRepeat() ",
                        "icons": [
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
                            "data": " Returns whether the backgorund of the current A2DComponent object is set to repeat and its numerical iterations. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int repe = object.GetOptBackgroundRepeat();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " Returns the repeat amount of the background image"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " A2DImageProperties * GetOptBackgroundProperties() ",
                        "icons": [
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
                            "data": " Returns a pointer to the aOptBackgroundProps object within the A2DComponent object. Allows user access to background size, repeat, etc. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$A2DImageProperties * object2 = object.GetOptBackgroundProperties();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DImageProperties * ",
                                    "description": " Pointer to the aOptBackgroundProps object "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackground(LPCWSTR * xOptBackgroundImage, int xOptBackroundPositionX, int xOptBackroundPositionY, int xOptBackroundSizeX, int xOptBackroundSizeY, int xOptBackgroundColor, int xOptBackgroundRepeat) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " ///////////////// ",
                                    "description": " an A2DRect pointer to the desired A2DRect object "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Method that sets the A2DRect pointer of the protected aClip pointer of the A2DAbstractTexture class. This allows the user to set a new specific \"area\" targeted by the specific A2DAbstractTexture object through referencing another A2DRect object in memory already."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$A2DRect object2;$ object.SetClip(&object2);"
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
                        "title": " void SetOptBackgroundImage(LPCWSTR * xOptBackgroundImage) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " LPCWSTR * ",
                                    "description": " LPCWSTR pointer to the name of the source image "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Allows the user to set the source of the background image used by the reference A2DComponent object through a Long Wide String object indicating the source image's name/information. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$LPCWSTR * colora;$object2 = object.SetOptBackgroundImage(colora);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackgroundPositionX(int xOptPositionX) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " the cartesian x-coordinate of the background image "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the current background position's x-coordinate (of the specified A2Dcomponenent object) as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int posx;$object.SetOptBackgroundPositionX(posx);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackgroundPositionY(int xOptPositionY) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " the cartesian y-coordinate of the background image "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the current background position's y-coordinate (of the specified A2Dcomponenent object) as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int posy;$object.SetOptBackgroundPositionY(posy);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackgroundSizeX(int xOptSizeX) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " The cartesian horizontal size of the background image "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the current background position's size width-wise (distance between the leftmost and rightmost x-coordinates) of the specified A2Dcomponenent object as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int sizex;$bject.SetOptBackgroundSizeX(sizex);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackgroundSizeY(int xOptSizeY) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " The cartesian horizontal size of the background image "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the current background position's size length-wise (distance between the bottom and top y-coordinates) of the specified A2Dcomponenent object as an integer. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int sizey;$bject.SetOptBackgroundSizeY(sizey);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackgroundColor(int xOptColor) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " The CSS reference number of the background color "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets the current background color of the specified A2Dcomponenent object. The color is a CSS reference via an int representation. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int cola;$bject.SetOptBackgroundColor(cola);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void SetOptBackgroundRepeat(int xOptRepeat) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " int ",
                                    "description": " int representation of the repeat amount of the background image "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets whether the backgorund of the current A2DComponent object is set to repeat and its numerical iterations. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$int repe;$object.SetOptBackgroundRepeat(repe);"
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
                        "title": " void SetOptBackgroundProperties(A2DImageProperties * xOptBackgroundProps) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " A2DImageProperties * ",
                                    "description": " Pointer to the aOptBackgroundProps object "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Sets a pointer to the desired aOptBackgroundProps object within the A2DComponent object. Allows user to set background size, repeat, etc. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$A2DImageProperties * object2;$object.SetOptBackgroundProperties(object2);"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void RenderComponent(A2DRenderData * xRenderData) ",
                        "icons": [
                                "methodMutator",
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
                            "data": " Switches the active buffer to texture, moves the content from texturebuffer to backbuffer, renders the component through the internal DrawImage method, calls children updates. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$A2DRenderData * object2;$ object.RenderComponent(object2);"
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
                        "title": " virtual void RenderComponentBorder(A2DRenderData * xRenderData) ",
                        "icons": [
                                "methodMutator",
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
                            "data": " Switches the active buffer to texture, moves the content from texturebuffer to backbuffer, renders component border. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$A2DRenderData * object2;$ object.RenderComponentBorder(object2);"
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
                        "title": " virtual void Render(A2DRenderData * xRenderData) ",
                        "icons": [
                                "methodMutator",
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
                            "data": " Switches the active buffer to texture, moves the content from texturebuffer to backbuffer, renders the component, switch the active buffer to backbuffer, calls children updates, renders component border. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$A2DRenderData * object2;$ object.Render(object2);"
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
                        "title": " virtual HRESULT Initialize()",
                        "icons": [
                                "methodVirtual",
                                "methodConstructor"
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
                            "data": "Initializes the aOptBackgroundProps object within the A2DComponent object, initializes the A2DImageProperties. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$object.Initialize();//Initializes an A2DAbstractComponent object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`."
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
                            "data": " Deletes the previously initialized objects within the A2DAbstractTexture class. Without the A2DImageProperties object, the A2DComponent object is effictively Deinitialized. "
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$object.Initialize();$object.Deinitialize();"
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
                        "title": "bool A2DComponent::operator==(A2DAbstract * xAbstract)",
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
                            "data": "A2DComponent object;$A2DRenderData object2;$ bool check = object2==object; //check = false"
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
                        "title": "LPCWSTR A2DComponent::ToString()",
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
                            "data": "Returns a string representation of the A2DComponent instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DComponent` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$cout << \"Class type : \" << object.ToString() << endl;"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " LPCWSTR ",
                                    "description": "a wide string representation of the A2D object."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": "LPCWSTR A2DComponent::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DComponent` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DComponent object;$cout << \"Class type : \" << object.GetClass() << endl;"
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
            "title": "A2DAbstractShape",
            "background": "images/e.jpg",
            "dataType": "class",
            "description": "This class is the hierarchial parent class of all shapes in the Aurora2D library. All shape subclasses inherit and must override almost all methods within this class. It defines shape-environment interactions within the entire A2D structure.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstractShape() ",
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
                            "data": "Default Constructor that initializes an A2DAbstractShape object. Allocates memory in the heap/stack to be assigned to an A2DAbstractShape object. "
                        },
                        {
                            "type": "code",
                            "data": " A2DAbstractShape object;//creates the A2DAbstractShape object"
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
                        "title": " ~A2DAbstractShape() ",
                        "icons": [
                                "methodDeconstructor"
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
                            "data": "Deallocates memory assigned to the previously created A2DAbstractShape object. Default constructor, will be called by the system even if the user doesn't call it explicitly."
                        },
                        {
                            "type": "code",
                            "data": "A2DRenderData object;//once the program or scope is exited, the object will be destroyed"
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
                        "title": " virtual HRESULT Map() = 0; ",
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
                            "data": " Purely virtual method in the A2DAbstractShape class that must be overridden by every subsequent `Shape` class. Used to implement mapping of the shape in the graphical environment. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.Map();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`.`"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual HRESULT Update() = 0; ",
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
                            "data": " Purely virtual method in the A2DAbstractShape class that must be overridden by every subsequent `Shape` class. Used to update Shape information regarding size/positioning/mapping, etc. Dependent on subclass implementation. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.Update();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void Render() = 0; ",
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
                            "data": "Purely virtual method in the A2DAbstractShape class that must be overridden by every subsequent `Shape` class. Renders the shape within it's specified container, consistent with whatever parameters invoked by the subclass implementing it."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.Render();"
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
                        "title": " virtual HRESULT SetAsTexture() = 0; ",
                        "icons": [
                                "methodMutator",
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
                            "data": "Purely virtual method in the A2DAbstractShape class that must be overridden by every subsequent `Shape` class. Used to set the texture as per the subclass's specific implementation for the specified A2DAbstractShape object."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.SetAsTexture();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void SetConstraints() = 0; ",
                        "icons": [
                                "methodMutator",
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
                            "data": "Purely virtual method in the A2DAbstractShape class that must be overridden by every subsequent `Shape` class. Used to set the appropriate constraints of the A2DAbstractShape object, as dictatd by the specific subclass implementing this method."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.SetConstraints();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void SetLocation() = 0; ",
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
                            "data": "Purely virtual method in the A2DAbstractShape class that must be overridden by every subsequent `Shape` class. Used to set the new location of the A2DAbstractShape object, as dictatd by the specific subclass implementing this method."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$ object.SetLocation();"
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
                        "title": " virtual void InitializeBuffer() = 0; ",
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
                            "data": "Initializes the buffers and their handles, pointers etc that the A2DAbstractShape object requires. Essentially preps the object to be processed and displayed by the graphical and rendering environments by declaring its fundamental information (size, texture, vertices, etc)."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.InitializeBuffer();"
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
                        "title": " virtual void UpdateBuffer() = 0; ",
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
                            "data": "Updates the buffers and their handles, pointers etc that the A2DAbstractShape object requires. Updates the processing information of the object to be processed and displayed by the graphical and rendering environments."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.UpdateBuffer();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
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
                            "data": "Destroys the prevoiusly created resources of an A2DAbstractShape object. A purely virtual method in the `A2DAbstractShape` class, must be overridden by every shape subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.CreateResources(xRenderData1);$object.DestroyResources();"
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
                            "data": "Initializes whatever buffers, handles, pointers etc that the A2DAbstractShape object requires and returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$object.Initialize();//Initializes an A2DAbstractShape object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`."
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
                            "data": "A2DAbstractShape object;$object.Initialize();$object.Deinitialize();"
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
                        "title": "bool A2DAbstractShape::operator==(A2DAbstractShape * xAbstractShape)",
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
                                    "description": "an A2DAbsractShape pointer"
                                },
                            ]
                        },
                        {
                            "type": "important",
                            "data": "The equals method for class Object implements the most discriminating possible equivalence relation on objects; that is, for any non-null reference values `x` and `y`, this method returns `true` if and only if `x` and `y` refer to the same object (`x == y` has the value `true`). Note that it is generally necessary to override the `hashCode` method whenever this method is overridden, so as to maintain the general contract for the hashCode method,which states that equal objects must have equal hash codes."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbsractShape object;$A2DAbstractShape object2;$ bool check = object2==object; //check = false"
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
                        "title": "LPCWSTR A2DAbstractShape::ToString()",
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
                            "data": "Returns a string representation of the A2DAbstractShape instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DAbstractShape` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$cout << \"Class type : \" << object.ToString() << endl;"
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
                        "title": "LPCWSTR A2DAbstractShape::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DAbstractShape` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractShape object;$cout << \"Class type : \" << object.GetClass() << endl;"
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
            "title": "A2DAbstractTexture",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": " The abstract or root class for setting and manipulating textures within the Aurora2D library. Allows selection of a specific subsection of the texture on which to implement some new texture. Subclasses override and extend A2DAbstractTexture unique to their specific texture implemenation.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstractTexture(A2DBackBuffer * xBackBuffer) ",
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
                            "data": "Default Constructor that initializes an A2DAbstractTexture object. Allocates memory in the heap or stack depending on the scope. Initializes encapsulated data such as aClip and aResource which are used by other methods through the class. "
                        },
                        {
                            "type": "code",
                            "data": " A2DAbstractTexture object;//creates the A2DAbstractTexture object"
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
                        "title": " ~A2DAbstractTexture() ",
                        "icons": [
                                "methodDeconstructor"
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
                            "data": "Deallocates memory assigned to the previously created A2DAbstractTexture object. Default destructor, will be called by the system even if the user doesn't call it explicitly."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;//once the program or scope is exited, the object will be destroyed"
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
                        "title": " virtual A2DDims * GetSize(); ",
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
                            "data": " Method that returns the A2DDims pointer to the protected aSize pointer of the A2DAbstractTexture class. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$ A2DDims * object2 = object.GetSize();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DDims * ",
                                    "description": " Returns an A2DDims pointer to the aSize object of A2DAbstractTexture"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual A2DRect * GetClip(); ",
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
                            "data": " Method that returns the A2DRect pointer to the protected aClip pointer of the A2DAbstractTexture class. This allows the user to retrieve the specific \"area\" targeted by the specific A2DAbstractTexture object."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$ A2DRect * object2 = object.GetClip();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DRect * ",
                                    "description": " Returns an A2DRect pointer to the aClip object of A2DAbstractTexture"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void SetClip(A2DRect * xClip) ",
                        "icons": [
                                "methodMutator",
                                "methodVirtual"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xClip ",
                                    "description": " an A2DRect pointer to the desired A2DRect object "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Method that sets the A2DRect pointer of the protected aClip pointer of the A2DAbstractTexture class. This allows the user to set a new specific \"area\" targeted by the specific A2DAbstractTexture object through referencing another A2DRect object in memory already."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$A2DRect object2;$ object.SetClip(&object2);"
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
                        "title": " ID3D10ShaderResourceView * GetResource(); ",
                        "icons": [
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
                            "data": " Method that returns the ID3D10ShaderResourceView pointer to the protected aResource object within the A2DAbstractTexture class. This in turn proves access to the object's shader-resource-view interface taht specifies the subresources a shader can access during rendering. Examples of shader resources include a constant buffer, a texture buffer, a texture or a sampler."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$ID3D10ShaderResourceView * object2 = object.GetResource();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " ID3D10ShaderResourceView * ",
                                    "description": " Returns an ID3D10ShaderResourceView pointer to the aResource object of A2DAbstractTexture"
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual bool hasAlpha(); ",
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
                            "data": " Method that returns the whether the Alpha property is included within the specific A2DAbstractTexture object. By default this returns `true`, because by design every A2DAbstractTexture object has this property enabled."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$bool check = object.hasAlpha(); //returns true"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " bool ",
                                    "description": " Returns success or failiure regarding presense of the Alpha property. A2DAbstractTexture always returns `true`."
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual HRESULT CreateResources() = 0; ",
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
                            "data": " A method that Creates the necessary resources for an A2DAbstractTexture object. A purely virtual method in the `A2DAbstractTexture` class, must be overridden by every subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$object.CreateResources();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void Update() = 0; ",
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
                            "data": " Purely virtual method in the A2DAbstractTexture class that must be overridden by every subsequent `A2DAbstractTexture` class. Used to update texture-specific information that is dependent on the subclass' implementation. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$object.Update();"
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
                        "title": " virtual void Render() = 0; ",
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
                            "data": "Purely virtual method in the A2DAbstractTexture class that must be overridden by every subsequent `A2DAbstractTexture` class. Renders the texture within it's specified rectangular dimension, consistent with whatever parameters invoked by the subclass implementing it."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$object.Render();"
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
                        "title": "virtual void DestroyResources() ",
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
                            "data": "Destroys the prevoiusly created resources of an A2DAbstractTexture. Specifically sets the ID3D10ShaderResourceView pointer to the aResource variable within the A2DAbstractTexture class to `0`, effectively freeing whatever object in memory was prevoiusly being pointed to."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$object.CreateResources();$object.DestroyResources();"
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
                        "title": " virtual HRESULT Initialize()",
                        "icons": [
                                "methodVirtual",
                                "methodConstructor"
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
                            "data": "Initializes the aClip object within the A2DAbstractTexture class and sets its x,y coordinates as well as width and height to match the enclosed A2DDims object of the class. Returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$object.Initialize();//Initializes an A2DAbstractTexture object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`."
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
                            "data": " Deletes the aSize and aClip variables within the A2DAbstractTexture class. Without the A2DRect and A2DDims objects, the A2DAbstractTexture object is effictively Deinitialized. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$object.Initialize();$object.Deinitialize();"
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
                        "title": "bool A2DAbstractTexture::operator==(A2DAbstract * xAbstract)",
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
                            "data": "A2DAbstractTexture object;$A2DRenderData object2;$ bool check = object2==object; //check = false"
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
                        "title": "LPCWSTR A2DAbstractTexture::ToString()",
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
                            "data": "Returns a string representation of the A2DAbstractTexture instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DAbstractTexture` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$cout << \"Class type : \" << object.ToString() << endl;"
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
                        "title": "LPCWSTR A2DAbstractTexture::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DAbstractTexture` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractTexture object;$cout << \"Class type : \" << object.GetClass() << endl;"
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
            "title": "A2DCamera",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": "This class creates and intializes the necessary matrices, buffers, and handles to setup the camera of the render/graphics system. Enables manipulation of the view and camera data that orients the components and other graphical data in the way that is ultiamately presented to the user.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DCamera() ",
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
                            "data": "Default Constructor that initializes an A2DCamera object. Allocates memory in the heap/stack (depending on the scope) to be assigned to an A2DCamera object. Initializes aCameraprops (the class's protected A2DCameraProperties object) with`NULL` parameters passed to indicate an initial and basic instance."
                        },
                        {
                            "type": "code",
                            "data": " A2DCamera object;//creates the A2DRenderData object"
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
                        "title": " A2DCamera(A2DCameraProperties * xCameraProps) ",
                        "icons": [
                                "methodConstructor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xCameraProps",
                                    "description": " An A2DCameraProperties object pointer"
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Constructor that initializes an A2DCamera object. Allocates memory in the heap/stack (depending on the scope) to be assigned to an A2DCamera object. Initializes aCameraprops (the class's protected A2DCameraProperties object) with the specified A2DCameraProperties object passed."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object(xCameraProps);"
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
                        "title": " ~A2DCamera() ",
                        "icons": [
                                "methodDeconstructor"
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
                            "data": "Deallocates memory assigned to the previously created A2DCamera object. Default constructor, will be called by the system even if the user doesn't call it explicitly."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;//once the program or scope is exited, the object will be destroyed"
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
                        "title": " D3DXMATRIX * GetViewMatrix(); ",
                        "icons": [
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Returns the A2DCamera object's ViewMatrix through a Direct3D object pointer. Enables access to the exact information of the A2DCamera object's view Matrix."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$D3DXMATRIX * objec2 = object.GetViewMatrix();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " D3DXMATRIX* ",
                                    "description": " Returns a D3DXMATRIX pointer pointing to the D3d View Matrix "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " A2DCameraProperties * GetProperties(); ",
                        "icons": [
                                "methodAccessor"
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Returns the A2DCamera object's aCameraProps A2DCameraProperties object through a A2DCameraProperties object pointer. Enables access to the exact information of the A2DCamera object's protected variable aCameraprops."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$A2DCameraProperties * objec2 = object.GetProperties();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " A2DCameraProperties* ",
                                    "description": " Returns an A2DCameraProperties pointer to the aCameraprops protected object. "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " void CreateResources() ",
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
                            "data": " Initializes the A2DCamera object's properties and resources. Position, Yaw, Pitch, Roll, and Rotation are key properties which are created for the x,y, and z axes. The various associated Matrices and Transformation Coordinates are set appropriately."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$object.CreateResources();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " NONE ",
                                    "description": "  "
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
                            "data": "Initializes the aCameraprops variable, in turn initializing the A2DCameraProperties object associated with A2DCamera. Also initializes the associated ViewMatrix."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$object.Initialize();//Initializes an A2DCamera object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. A2DCamera returns `S_OK`"
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
                            "data": "Deinitializes the aCameraprops variable, in turn deinitializing the A2DCameraProperties object associated with A2DCamera. Also deinitializes the associated ViewMatrix."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$object.Initialize();$object.Deinitialize();"
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
                        "title": "bool A2DCamera::operator==(A2DAbstract * xAbstract)",
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
                            "data": "A2DCamera object;$A2DAbsract object2;$ bool check = object2==object; //check = false"
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
                        "title": "LPCWSTR A2DCamera::ToString()",
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
                            "data": "Returns a string representation of the A2DCamera instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DCamera` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$cout << \"Class type : \" << object.ToString() << endl;"
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
                        "title": "LPCWSTR A2DCamera::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DCamera` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DCamera object;$cout << \"Class type : \" << object.GetClass() << endl;"
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
            "title": "A2DCameraProperties",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": "A supplementary yet fundamental class for all vital Components in Aurora2D except top-level containers. Extended and utitilzed by all top-level component classes that work in the \"pipeline\" process of rendering the graphics and components. Top-level A2D containers are specialized components that provide a place for other A2D components to paint themselves. Based on the JComponent Class.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstractPipelineComponent(A2DBackBuffer * xBackBuffer) ",
                        "icons": [
                                "methodConstructor",
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xBackBuffer ",
                                    "description": " An A2DBackBuffer pointer to an A2DBackBuffer object "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Constructor that initializes an A2DAbstractPipelineComponent object, allocating memory for it either in the heap or stack depending on scope. Takes in an A2DBackBuffer object and initializes it as a protected variable as part of the A2DAbstractPipelineComponent class."
                        },
                        {
                            "type": "code",
                            "data": " A2DAbstractPipelineComponent object;//creates the A2DAbstractPipelineComponent object"
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
                        "title": " ~A2DAbstractPipelineComponent() ",
                        "icons": [
                                "methodDeconstructor"
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
                            "data": "Deallocates memory assigned to the previously created A2DAbstractPipelineComponent object. Default constructor, will be called by the system even if the user doesn't call it explicitly."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;//once the program or scope is exited, the object will be destroyed"
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
                        "title": " virtual HRESULT CreateResources() ",
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
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Initializes the A2DABSTRACTCOMPONENT object's properties and resources. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.CreateResources();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns success or failiure through an HRESULT qualifier "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void Update() = 0; ",
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
                            "data": " Purely virtual method in the A2DAbstractPipelineComponent class that must be overridden by every subsequent `Pipeline Component` class. Used to update Component information that is dependent on the subclass' implementation. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Update();"
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
                        "title": " virtual void Render() = 0; ",
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
                            "data": "Purely virtual method in the A2DAbstractPipelineComponent class that must be overridden by every subsequent `Pipeline Component` class. Renders the Component within it's specified container, consistent with whatever parameters invoked by the subclass implementing it."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Render();"
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
                            "data": "Destroys the prevoiusly created resources of an A2DAbstractPipelineComponent object. A purely virtual method in the `A2DAbstractPipelineComponent` class, must be overridden by every pipeline component subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.CreateResources(xRenderData1);$object.DestroyResources();"
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
                        "title": " virtual HRESULT Initialize()",
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
                            "data": "Initializes whatever buffers, handles, pointers etc that the A2DAbstractPipelineComponent object requires and returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Initialize();//Initializes an A2DAbstractPipelineComponent object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. S_OK"
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
                            "data": "Deallocates memory assigned to the previously created object and unassigns all buffers, handles, pointers, etc. to the object. This is a pure virtual funciton in the A2DAbstractPipelineComponent class, so note that it is generally necessary to override this method in all subclasses."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Initialize();$object.Deinitialize();"
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
                        "title": "bool A2DAbstractPipelineComponent::operator==(A2DAbstract * xAbstract)",
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
                            "data": "A2DAbstractPipelineComponent object;$A2DRenderData object2;$ bool check = object2==object; //check = false"
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
                        "title": "LPCWSTR A2DAbstractPipelineComponent::ToString()",
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
                            "data": "Returns a string representation of the A2DAbstractPipelineComponent instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DAbstractPipelineComponent` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$cout << \"Class type : \" << object.ToString() << endl;"
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
                        "title": "LPCWSTR A2DAbstractPipelineComponent::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DAbstractPipelineComponent` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$cout << \"Class type : \" << object.GetClass() << endl;"
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
            "title": "A2DAbstractPipelineComponent",
            "background": "images/g.jpg",
            "dataType": "class",
            "description": "A supplementary yet fundamental class for all vital Components in Aurora2D except top-level containers. Extended and utitilzed by all top-level component classes that work in the \"pipeline\" process of rendering the graphics and components. Top-level A2D containers are specialized components that provide a place for other A2D components to paint themselves. Based on the JComponent Class.",
            "extends": [],
            "blocks": [
                {
                    "header": {
                        "type": "code",
                        "title": " A2DAbstractPipelineComponent(A2DBackBuffer * xBackBuffer) ",
                        "icons": [
                                "methodConstructor",
                            ]
                    },
                    "sections": [
                        {
                            "type": "params",
                            "args": [
                                {
                                    "title": " xBackBuffer ",
                                    "description": " An A2DBackBuffer pointer to an A2DBackBuffer object "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": "Default Constructor that initializes an A2DAbstractPipelineComponent object, allocating memory for it either in the heap or stack depending on scope. Takes in an A2DBackBuffer object and initializes it as a protected variable as part of the A2DAbstractPipelineComponent class."
                        },
                        {
                            "type": "code",
                            "data": " A2DAbstractPipelineComponent object;//creates the A2DAbstractPipelineComponent object"
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
                        "title": " ~A2DAbstractPipelineComponent() ",
                        "icons": [
                                "methodDeconstructor"
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
                            "data": "Deallocates memory assigned to the previously created A2DAbstractPipelineComponent object. Default constructor, will be called by the system even if the user doesn't call it explicitly."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;//once the program or scope is exited, the object will be destroyed"
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
                        "title": " virtual HRESULT CreateResources() ",
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
                                    "title": " NONE ",
                                    "description": " "
                                }
                            ]
                        },
                        {
                            "type": "important",
                            "data": " Initializes the A2DABSTRACTCOMPONENT object's properties and resources. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.CreateResources();"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns success or failiure through an HRESULT qualifier "
                                }
                            ]
                        }
                    ]
                },
                {
                    "header": {
                        "type": "code",
                        "title": " virtual void Update() = 0; ",
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
                            "data": " Purely virtual method in the A2DAbstractPipelineComponent class that must be overridden by every subsequent `Pipeline Component` class. Used to update Component information that is dependent on the subclass' implementation. "
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Update();"
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
                        "title": " virtual void Render() = 0; ",
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
                            "data": "Purely virtual method in the A2DAbstractPipelineComponent class that must be overridden by every subsequent `Pipeline Component` class. Renders the Component within it's specified container, consistent with whatever parameters invoked by the subclass implementing it."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Render();"
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
                            "data": "Destroys the prevoiusly created resources of an A2DAbstractPipelineComponent object. A purely virtual method in the `A2DAbstractPipelineComponent` class, must be overridden by every pipeline component subclass."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.CreateResources(xRenderData1);$object.DestroyResources();"
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
                        "title": " virtual HRESULT Initialize()",
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
                            "data": "Initializes whatever buffers, handles, pointers etc that the A2DAbstractPipelineComponent object requires and returns whether it was successful."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Initialize();//Initializes an A2DAbstractPipelineComponent object, subclasses will also take care of whatever handles etc. that need to be initialized"
                        },
                        {
                            "type": "return",
                            "args": [
                                {
                                    "title": " HRESULT ",
                                    "description": " Returns an `HRESULT` value to indicate whether Initialization was successful. `0` indicates succes or \"no error \" and `1` indicates failiure or `COERROR`. S_OK"
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
                            "data": "Deallocates memory assigned to the previously created object and unassigns all buffers, handles, pointers, etc. to the object. This is a pure virtual funciton in the A2DAbstractPipelineComponent class, so note that it is generally necessary to override this method in all subclasses."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$object.Initialize();$object.Deinitialize();"
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
                        "title": "bool A2DAbstractPipelineComponent::operator==(A2DAbstract * xAbstract)",
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
                            "data": "A2DAbstractPipelineComponent object;$A2DRenderData object2;$ bool check = object2==object; //check = false"
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
                        "title": "LPCWSTR A2DAbstractPipelineComponent::ToString()",
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
                            "data": "Returns a string representation of the A2DAbstractPipelineComponent instance. In general, the `toString` method returns a string that \"textually represents\" this object. The result should be a concise but informative representation that is easy for a person to read. It is recommended that all subclasses override this method. The `toString` method for class `A2DAbstractPipelineComponent` returns a string consisting of the name of the class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$cout << \"Class type : \" << object.ToString() << endl;"
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
                        "title": "LPCWSTR A2DAbstractPipelineComponent::GetClass()",
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
                            "data": "Returns a Wide String representation of the A2D class being implemented. In general the `GetClass` method returns a string that \"textually\" represents a class. The result should be a short and simple representation easy to read and use in debugging. It is recommended that all subclasses override this method. The `GetClass` method for class `A2DAbstractPipelineComponent` returns a string consisting of the name of class."
                        },
                        {
                            "type": "code",
                            "data": "A2DAbstractPipelineComponent object;$cout << \"Class type : \" << object.GetClass() << endl;"
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