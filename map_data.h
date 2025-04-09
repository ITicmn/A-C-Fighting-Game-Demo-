#ifndef MAP_DATA_H
#define MAP_DATA_H

using namespace std;

map<string,map<string,string>> map_assets_data = {
    {"map1",{{"Background","assets/Maps/map1/background.png"},
             {"Platform1","assets/Maps/map1/platform1.png"},
             {"Platform2","assets/Maps/map1/platform2.png"},
             {"Platform3","assets/Maps/map1/platform3.png"}
            }
    },
    {"map2",{{"Background","assets/Maps/map2/background.png"},
             {"Platform1","assets/Maps/map2/platform1.png"}
            }
    },
    {"map3",{{"Background","assets/Maps/map3/background.png"},
             {"Platform1","assets/Maps/map3/platform1.png"}
            }
    },
    {"map4",{{"Background","assets/Maps/map4/background.png"}
            }
    }
};

map<string,map<string,array<int,5>>> map_data = {//Climable, Dropable, Movable
    {"map1",{{"Platform1",{131,285,0,1,0}},
             {"Platform2",{1331,285,0,1,0}},
             {"Platform3",{410,709,0,0,0}}
            }
    },
    {"map2",{{"Platform1",{381,571,1,0,0}}
            }
    },
    {"map3",{{"Platform1",{0,970,0,0,0}}
            }
    },
    {"map4",{{"Platform1",{0,970,0,0,0}}
            }
    }
};

#endif // MAP_DATA_H
