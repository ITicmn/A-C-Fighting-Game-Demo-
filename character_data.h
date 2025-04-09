#ifndef CHARACTER_ASSETS_H
#define CHARACTER_ASSETS_H

using namespace std;

map<string,map<string,map<string,string>>> character_assets_data = {
    {"Steve",{{"Stand",{
                        {"right","assets/Steve/Stand/right"},
                        {"left","assets/Steve/Stand/left"}
                       }
              },
              {"Walk",{
                        {"right","assets/Steve/Walk/right"},
                        {"left","assets/Steve/Walk/left"}
                      }
              },
              {"Drop",{
                        {"right","assets/Steve/Drop/right"},
                        {"left","assets/Steve/Drop/left"}
                      }
              },
              {"Jump",{
                        {"right","assets/Steve/Jump/right"},
                        {"left","assets/Steve/Jump/left"}
                      }
              },
              {"Damaged",{
                        {"right","assets/Steve/Damaged/right"},
                        {"left","assets/Steve/Damaged/left"}
                      }
              },
              {"Dash",{
                        {"right","assets/Steve/Dash/right"},
                        {"left","assets/Steve/Dash/left"}
                      }
              },
              {"Light Attack Stand",{
                        {"right","assets/Steve/Light Attack Stand/right"},
                        {"left","assets/Steve/Light Attack Stand/left"}
                      }
              },
              {"Light Attack Forward",{
                        {"right","assets/Steve/Light Attack Forward/right"},
                        {"left","assets/Steve/Light Attack Forward/left"}
                      }
              },
              {"Light Attack Downward",{
                        {"right","assets/Steve/Light Attack Downward/right"},
                        {"left","assets/Steve/Light Attack Downward/left"}
                      }
              },
              {"Heavy Attack Stand",{
                        {"right","assets/Steve/Heavy Attack Stand/right"},
                        {"left","assets/Steve/Heavy Attack Stand/left"}
                      }
              },
              {"Heavy Attack Forward",{
                        {"right","assets/Steve/Heavy Attack Forward/right"},
                        {"left","assets/Steve/Heavy Attack Forward/left"}
                      }
              },
              {"Heavy Attack Downward",{
                        {"right","assets/Steve/Heavy Attack Downward/right"},
                        {"left","assets/Steve/Heavy Attack Downward/left"}
                      }
              },
              {"Air Attack Downward",{
                        {"right","assets/Steve/Air Attack Downward/right"},
                        {"left","assets/Steve/Air Attack Downward/left"}
                      }
              },
              {"Air Attack Upward",{
                        {"right","assets/Steve/Air Attack Upward/right"},
                        {"left","assets/Steve/Air Attack Upward/left"}
                      }
              },
              {"Air Attack",{
                        {"right","assets/Steve/Air Attack/right"},
                        {"left","assets/Steve/Air Attack/left"}
                      }
              },
              {"Projectile",{
                        {"right","assets/Steve/Projectile/right"},
                        {"left","assets/Steve/Projectile/left"}
                      }
              }
             }
    }
};

map<string,map<string,float>> character_damage_data = {
    {"Steve",{{"Light Attack Stand",30},
              {"Light Attack Forward",30},
              {"Light Attack Downward",25},
              {"Heavy Attack Stand",40},
              {"Heavy Attack Forward",40},
              {"Heavy Attack Downward",0},
              {"Air Attack Downward",25},
              {"Air Attack Upward",25},
              {"Air Attack",20},
              {"Projectile",40}
             }
    }
};

#endif // CHARACTER_ASSETS_H
