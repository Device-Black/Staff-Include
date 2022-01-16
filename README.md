# Staff-Include
Include para sistema de admin com salvamento em SQLite

## Requer
a_samp.inc, a_sampdb.inc, foreach.inc, strlib.inc

## Funções
[cpp]
native STAFF_Init();
native GetAllStaffList();
native GetConnectedStaffList();
native AddPlayerToStaff(const username[], level);
native RemovePlayerFromStaff(const username[]);
native SetPlayerStaffLevel(playerid, level);
native GetPlayerStaffLevel(playerid);
native TogglePlayerStaffMode(playerid);
native GetPlayerStaffMode(playerid);
[/cpp]
