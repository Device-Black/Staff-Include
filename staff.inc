/*
 *	Include: Staff System
 *	Handler: SQLite
 *	Author: DeviceBlack
 */
 
#if defined staff_system
	#endinput
#endif
#define staff_system

#include    <a_samp>
#include	<a_sampdb>
#include	<foreach>
#include	<strlib>

#if defined BY_DeviceBlack
native STAFF_Init();
native GetAllStaffList();
native GetConnectedStaffList();
native AddPlayerToStaff(const username[], level);
native RemovePlayerFromStaff(const username[]);
native SetPlayerStaffLevel(playerid, level);
native GetPlayerStaffLevel(playerid);
native TogglePlayerStaffMode(playerid);
native GetPlayerStaffMode(playerid);
#endif

#define IsPlayerInStaffMode(%1) GetPlayerStaffMode(%1)

forward OnPlayerToggleStaffMode(playerid);
forward OnPlayerReceiveStaffLevel(playerid);

// ------ [ NAO OUSA MEXER SE NAO SOUBER ]

// --- [ VARIAVEIS ]

new
	DB:staff_query,
	DBResult:staff_cache,
	Iterator:Staff<MAX_PLAYERS>;

// --- [ FAKE NATIVES ]

STAFF_Init()
{
	staff_query = db_open("server.db");
	db_free_result(db_query(staff_query, "CREATE TABLE IF NOT EXISTS Admins (User VARCHAR(24) NOT NULL, Level INTEGER NOT NULL, PRIMARY KEY(User));"));
}

stock GetAllStaffList()
{
	new output[4096];
	staff_cache = db_query(staff_query, "SELECT * FROM Admins;");
	do
	{
		new username[24];
		db_get_field_assoc(staff_cache, "User", username, sizeof username);
		new level = db_get_field_assoc_int(staff_cache, "Level");
		strcat(output, sprintf("\nUser: %s\nLevel: %d\n", username, level));
	}
	while(db_next_row(staff_cache));
	db_free_result(staff_cache);
	return output;
}

stock GetConnectedStaffList()
{
	new output[4096];
	foreach(new player : Staff)
	{
		new username[24];
		GetPlayerName(player, username, sizeof username);
		strcat(output, sprintf("\nUser: %s\nLevel: %d\n", username, GetPlayerStaffLevel(player)));
	}
	return output;
}

stock SetPlayerStaffLevel(playerid, level)
{
	new username[24];
	GetPlayerName(playerid, username, sizeof username);
	if(level > 0) AddPlayerToStaff(username, level);
	else RemovePlayerFromStaff(username);
	CallLocalFunction("OnPlayerReceiveStaffLevel", "d", playerid);
}

stock GetPlayerStaffLevel(playerid)
{
	new username[24];
	GetPlayerName(playerid, username, sizeof username);
	staff_cache = db_query(staff_query, sprintf("SELECT Level FROM Admins WHERE User='%s';", username));
	new staffLevel = db_get_field_int(staff_cache);
	db_free_result(staff_cache);
	return staffLevel;
}

stock TogglePlayerStaffMode(playerid)
{
	new username[24];
	GetPlayerName(playerid, username, sizeof username);
	if(GetPlayerStaffLevel(playerid))
	{
		if(Iter_Contains(Staff, playerid)) Iter_Remove(Staff, playerid);
		else Iter_Add(Staff, playerid);
		CallLocalFunction("OnPlayerToggleStaffMode", "d", playerid);
		return 1;
	}
	return 0;
}

stock GetPlayerStaffMode(playerid)
{
	return Iter_Contains(Staff, playerid);
}

// --- [ FUNCTIONS ]

AddPlayerToStaff(const username[], level)
{
	db_free_result(db_query(staff_query, sprintf("INSERT OR REPLACE INTO Admins (User, Level) VALUES ('%s', %d);", username, level)));
}

RemovePlayerFromStaff(const username[])
{
	db_free_result(db_query(staff_query, sprintf("DELETE FROM Admins WHERE User='%s';", username)));
}

// --- [ HOOK ]

public OnPlayerDisconnect(playerid, reason)
{
	if(Iter_Contains(Staff, playerid))
	{
		Iter_Remove(Staff, playerid);
	}
	#if defined STAFF_PlayerDisconnect
		return STAFF_PlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect STAFF_PlayerDisconnect
#if defined STAFF_PlayerDisconnect
	forward STAFF_PlayerDisconnect(playerid, reason);
#endif


