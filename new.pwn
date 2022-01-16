#include <a_samp>
#include <sscanf2>
#include <staff>
#include <strlib>
#include <zcmd>

#define 	SENHA_ADMIN	"staffsystem"

public OnGameModeInit()
{
	// Ira criar o arquivo se nao existir e junto a tabela de dados
	// Se nao usar essa aqui, as outras funcoes nao irao funcionar
	STAFF_Init();
	return 1;
}

public OnPlayerToggleStaffMode(playerid)
{
	new pname[24];
	GetPlayerName(playerid, pname, sizeof pname);
	if(GetPlayerStaffMode(playerid))
	{
		SendClientMessageToAll(-1, sprintf("| INFO | %s iniciou o modo staff!", pname));
	}
	else SendClientMessageToAll(-1, sprintf("| INFO | %s encerrou o modo staff!", pname));
	return 1;
}

public OnPlayerReceiveStaffLevel(playerid)
{
	new pname[24];
	GetPlayerName(playerid, pname, sizeof pname);
	if(GetPlayerStaffLevel(playerid))
	{
		SendClientMessageToAll(-1, sprintf("| INFO | %s pertence a staff!", pname));
	}
	else SendClientMessageToAll(-1, sprintf("| INFO | %s nao pertence a staff!", pname));
	return 1;
}

CMD:admins(playerid)
{
	// Ira mostrar uma dialog com uma lista staffs em modo de trabalho
	ShowPlayerDialog(playerid, 489, DIALOG_STYLE_MSGBOX, "Lista de Staff:", GetConnectedStaffList(), "Fechar", "");
	return 1;
}

CMD:viraradmin(playerid, params[])
{
	if(isequal(params, SENHA_ADMIN))
	{
		// Adicionar staff pelo id do jogador in-game
		// Obs: se o level for 0 entao ele sera retirado!
		// A callback "OnPlayerReceiveStaffLevel" sera chamada

		SetPlayerStaffLevel(playerid, 10);
		SendClientMessage(playerid, -1, sprintf("| INFO | Voce virou administrador nivel %d", GetPlayerStaffLevel(playerid)));
		return 1;
	}
	return 0;
}

new StaffSkin[MAX_PLAYERS];

CMD:staff(playerid)
{
	if(TogglePlayerStaffMode(playerid))
	{
		// if(IsPlayerInStaffMode(playerid))
		if(GetPlayerStaffMode(playerid))
		{
			StaffSkin[playerid] = GetPlayerSkin(playerid);
			SetPlayerSkin(playerid, 217);
			SendClientMessage(playerid, -1, "| INFO | Voce entrou no modo de trabalho!");
		}
		else
		{
			SetPlayerSkin(playerid, StaffSkin[playerid]);
			SendClientMessage(playerid, -1, "| INFO | Voce saiu do modo de trabalho!");
		}
	}
	else SendClientMessage(playerid, -1, "| ERRO | Comando exclusivo para equipe staff!");
	return 1;
}

main()
{
	// Adicionar staff pelo nickname
	AddPlayerToStaff("DeviceBlack", 10);
	print(GetAllStaffList());
}


