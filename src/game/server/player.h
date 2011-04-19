/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_PLAYER_H
#define GAME_SERVER_PLAYER_H

// this include should perhaps be removed
#include "entities/character.h"
#include "gamecontext.h"

// player object
class CPlayer
{
	MACRO_ALLOC_POOL_ID()
	
public:
	CPlayer(CGameContext *pGameServer, int ClientID, int Team);
	~CPlayer();

	void Init(int CID);

	void TryRespawn();
	void Respawn();
	void SetTeam(int Team);
	int GetTeam() const { return m_Team; };
	int GetCID() const { return m_ClientID; };
	
	void Tick();
	void PostTick();
	void Snap(int SnappingClient);

	void OnDirectInput(CNetObj_PlayerInput *NewInput);
	void OnPredictedInput(CNetObj_PlayerInput *NewInput);
	void OnDisconnect(const char *pReason);
	
	void KillCharacter(int Weapon = WEAPON_GAME);
	CCharacter *GetCharacter();
	
	//---------------------------------------------------------
	// this is used for snapping so we know how we can clip the view for the player
	vec2 m_ViewPos;

	// states if the client is chatting, accessing a menu etc.
	int m_PlayerFlags;

	// used for snapping to just update latency if the scoreboard is active
	int m_aActLatency[MAX_CLIENTS];

	// used for spectator mode
	int m_SpectatorID;

	bool m_IsReady;
	
	//
	int m_Vote;
	int m_VotePos;
	//
	int m_LastVoteCall;
	int m_LastVoteTry;
	int m_LastChat;
	int m_LastSetTeam;
	int m_LastSetSpectatorMode;
	int m_LastChangeInfo;
	int m_LastEmote;
	int m_LastKill;
	
	// TODO: clean this up
	struct 
	{
		char m_SkinName[64];
		int m_UseCustomColor;
		int m_ColorBody;
		int m_ColorFeet;
	} m_TeeInfos;
	
	int m_RespawnTick;
	int m_DieTick;
	int m_Score;
	int m_ScoreStartTick;
	bool m_ForceBalanced;
	int m_LastActionTick;
	struct
	{
		int m_TargetX;
		int m_TargetY;
	} m_LatestActivity;

	// network latency calculations	
	struct
	{
		int m_Accum;
		int m_AccumMin;
		int m_AccumMax;
		int m_Avg;
		int m_Min;
		int m_Max;	
	} m_Latency;
	
			//War3
	void init_rpg();
	void reset_all();
	bool choose_ability(int choice);

	//Levels var
	int lvl;
	int nextlvl;
	int xp;
	int leveled;
	bool levelmax;
	
	//Human vars
	int human_armor;
	int human_mole;
	bool human_special;
	//For human killing themself for mole
	bool suicide;

	//Orcs var
	int orc_dmg;
	int orc_reload;
	bool orc_special;

	//Undead vars
	int undead_taser;
	int undead_taser_tick;
	int undead_vamp;
	void vamp(int amount);
	bool undead_special;
	bool exploded;

	//Elf vars
	int elf_poison;
	int poisoned;
	int poison_start_tick;
	int start_poison;
	int poisoner;
	int elf_mirror;
	int mirrordmg_tick;
	int mirrorlimit;
	bool elf_special;

	//Tauren vars
	bool tauren_special;
	int tauren_hot;
	int tauren_ressurect;
	bool ressurected;
	int hot;
	int hot_start_tick;
	int start_hot;
	int hot_from;
	vec2 death_pos;
	bool invincible;
	int invincible_start_tick;
	bool healed;
	int heal_tick;
	int heal_from;
	int started_heal;
	bool death_tile;
	int bounces;
	int bounce_tick;
	CCharacter *heal_char;
	int last_healed;
	bool is_chain_heal;
	int chain_heal_from;

	//Other
	bool special_used;
	int special_used_tick;
	int race_name;

	//Unused skills


	//Functions
	int use_special(void);
	bool print_otherlvl(void);
	bool print_help(void);

	//Checking :D
	int force_race_tick;
	bool check;
	void check_skins(void);
	void check_name(void);

private:
	CCharacter *Character;
	CGameContext *m_pGameServer;
	
	CGameContext *GameServer() const { return m_pGameServer; }
	IServer *Server() const;
	
	//
	bool m_Spawning;
	int m_ClientID;
	int m_Team;
};

#endif