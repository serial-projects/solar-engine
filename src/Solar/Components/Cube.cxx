#include "Solar/Components/Cube.hxx"
namespace Solar
{
    namespace Components
    {
        void Cube::Init()
        {
            this->LoadModel(
                {
                    {-0.5f,-0.5f,-0.5f  },
                    {0.5f,-0.5f,-0.5f   },
                    {0.5f,0.5f,-0.5f    },
                    {0.5f,0.5f,-0.5f    },
                    {-0.5f,0.5f,-0.5f   },
                    {-0.5f,-0.5f,-0.5f  },

                    {-0.5f,-0.5f,0.5f   },
                    {0.5f,-0.5f,0.5f    },
                    {0.5f,0.5f,0.5f     },
                    {0.5f,0.5f,0.5f     },
                    {-0.5f,0.5f,0.5f    },
                    {-0.5f,-0.5f,0.5f   },

                    {-0.5f,0.5f,0.5f    },
                    {-0.5f,0.5f,-0.5f   },
                    {-0.5f,-0.5f,-0.5f  },
                    {-0.5f,-0.5f,-0.5f  },
                    {-0.5f,-0.5f,0.5f   },
                    {-0.5f,0.5f,0.5f    },

                    {0.5f,0.5f,0.5f     },
                    {0.5f,0.5f,-0.5f    },
                    {0.5f,-0.5f,-0.5f   },
                    {0.5f,-0.5f,-0.5f   },
                    {0.5f,-0.5f,0.5f    },
                    {0.5f,0.5f,0.5f     },

                    {-0.5f,-0.5f,-0.5f  },
                    {0.5f,-0.5f,-0.5f   },
                    {0.5f,-0.5f,0.5f    },
                    {0.5f,-0.5f,0.5f    },
                    {-0.5f,-0.5f,0.5f   },
                    {-0.5f,-0.5f,-0.5f  },

                    {-0.5f,0.5f,-0.5f   },
                    {0.5f,0.5f,-0.5f    },
                    {0.5f,0.5f,0.5f     },
                    {0.5f,0.5f,0.5f     },
                    {-0.5f,0.5f,0.5f    },
                    {-0.5f,0.5f,-0.5f   },
                },
                {
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},

                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},

                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},

                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                    {1.0f, 1.0f, 1.0f},
                },
                {},
                {}
            );
        }
        void Cube::Destroy()
        {
            this->UnloadModel();
        }
    };
};