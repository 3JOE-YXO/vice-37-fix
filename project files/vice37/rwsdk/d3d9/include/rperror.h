case CREATE_PLAYER:
	// �������� � ���� (�����, �����) ���������� 4 ���������
    CRunningScript::CollectParameters(this, 4);
	// this - ��� ������ (�����) CRunningScript, ������� ��������� ������, ��� ���������.

	// ������� �������� ���������� � ����������, ����� ���� "�����" � ��� ����������
    unsigned int playedId = ScriptParams[0];
	float x = ScriptParams[1];
	float y = ScriptParams[2];
	float z = ScriptParams[3];
	// ScriptParams - ��� ������ ����������. �����, ������� ���������� ��� ������ �����������.
	// �������� ����������, ��� � ���� ������� - 32 ��������. �������, ������� � ���������
	// ���������� � �������.

	// ���������, ��������� �� ������ � ����� 0. ���� ms_aInfoForModel - ������ ��������, ������� ���������
	// ��������� �������. ������ ����� ������� - 26316 ��������� (����� �������, ����� �������� ���������� �
	// ��������� ������������� ���� �������� (�������) ����).
    if ( CStreaming::ms_aInfoForModel[0].bLoadState != 1 )
	// ���� ������ �� ���������, ��������� �.
    {
		// ��������� ������ "player" � ���� 0
		CStreaming::RequestSpecialModel(0, "player", 0x1A);
		// ��, ������ ��� ������� ���������� �� ������ 038B.
		CStreaming::LoadAllRequestedModels(1);
    }
	// ��������� ��� ����-������. ������� ����������� ����.
    CPlayerPed::SetupPlayerPed(playedId);
	// � ���������� player ���������� ������ (�����) ������ � �������� playedId. ������ Players �������� 2 ��������
	// (2 ������)
    CPlayer *player = &CWorld::Players[playedId];
	// �����-�� ������� ��� ����-������... ��������������� DecisionMaker � ������������ melee-���� � 30.0
    sub_5E47E0(CWorld::Players[playedId].m_pPed, 2);
	// ������� ���� �� �������� ���� (��������� ��� ������ � ����� ����)
    CPlayerPed::DeactivatePlayerPed((CEntity *)playedId);
	// ���� ���������� z-��������� ������ �� (-100), ������� z-���������� ����������� (�����) �� ����������� (x,y)
    if(z <= -100.0)
        z = CWorld::FindGroundZForCoord(x, y);
	// ��������� � ���������� z ���������� �� ����� � ������ ����
    z += CEntity::GetDistanceFromCentreOfMassToBaseOfModel(player->m_pPed);
	// ������ ������������� ���� ������� � (x,y,z). ��������, ��� ��� ��� �� ���������� "�����������" ����. ���� ��
	// ������� ��� �� ����.
    CPlaceable::SetPos(player->m_pPed, x, y, z);
	// ��������� ���������� � ��������� CVector (����� ��� ��������� �������)
	CVector pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
	// ������� �� ������ ��� "�������" :) ����
    CTheScripts::ClearSpaceForMissionEntity(&pos, player->ped);
	// � ��� ������ ��������� ���� � ������ ���.
    CPlayerPed::ReactivatePlayerPed(playedId);
	// ������ ������. ����� ���������� ����� �������������� ������. ��� �����, ���� ��� �� �����, ������� ��
	// �������� � ����� � ���� ���������. �.�., ����� ������ - ��� ��� ����� � ������� ������� (�.�. ���� 0, ���� 1,
	// ������ � ���� ������ ������ ���� �����).
    ScriptParams[0] = playedId;
	// �������� �������� "�������" � ������ (�����)
    CRunningScript::StoreParameters(1);
	// ��� ����� �� ���� �������� ���������. ����� ��������������� ������ ������ (task'�). �������� ������ ��������
	// "playidles".
    allocated = CTask::operator new(28);
    if (allocated)
        CTaskSimpleProcessPlayerWeapon *task = CTaskSimpleProcessPlayerWeapon::CTaskSimpleProcessPlayerWeapon(allocated);
    else
        task = 0;
    CPedIntelligence *intelligence = player->m_pPed->intelligence;
    CPedTasks::AssignPrimaryTask(&intelligence->m_pedTasks, task, 4, 0);
    return 0;

������� CPlayerPed::SetupPlayerPed(unsigned int playedId). � ���� ������� ��������� ��� ��� ������.

void CPlayerPed::SetupPlayerPed(int playerId)
{
	// �������� ����� � ���� ����� ��� ������ ����.
    CPed *ped = PedPool::Allocate();
    if(ped)
		// ��� ������� - �����������. ��� "������" (��-��) ����, ������������� ��� ���� ������� ���������
		ped = CPlayerPed::CPlayerPed(ped, playerId, 0);
    else
		ped = 0;
	// ����������� ���� � ������ � id playerId.
    CWorld::Players[playerId].m_pPed = ped;
	// ���� ����� - �� ������, � ������ (�� ��������, ��� ���������� ���������� � ����), �� ������ ���� ���
	// PLAYER2.
    if(playerId == 1)
		ped->pedType = PLAYER2;
	// ������������� �������� � 0.
    CPlaceable::setRotation(CWorld::Players[playerId].m_pPed, 0.0, 0.0, 0.0);
	// �������� ���� � ������� ���.
    CWorld::Add((CEntity *)CWorld::Players[playerId].m_pPed);
	// ������� �������� - �� 100.
    CWorld::Players[playerId].m_pPed->weaponAccuracy = 100;
	// ������������� ���� isWastedBusted � 0.
    CWorld::Players[playerId].isWastedBusted = 0;
}

