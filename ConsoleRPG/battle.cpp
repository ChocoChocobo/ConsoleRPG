#include "battle.h"
#include "savesystem.h"
#include "user_interface.h"

void CheckWinLoseConditionPlayer(Character player)
{

}

void CheckWinLoseConditionEnemy(Character enemy)
{

}

// -------------------------- State
void BattleContext::TransitionToState(BattleState* state)
{
	std::cout << "\t\t���������� ����� ��������� �� ������ ���������" << typeid(*state).name() << std::endl;
	// ���� ������������ ��������� � ���������, ������� ������ ��������� �� ��������� � ������ �����
	if (this->state != nullptr)
	{
		delete this->state;
	}
	this->state = state;
	this->state->SetContext(this);
}

void PlayerTurnState::HandleChangeState()
{
	context->SetBattleStateEnum(EnemyTurnEnum);
	this->context->TransitionToState(new EnemyTurnState);
}

int PlayerTurnState::HandleAction(Character& player, Character& enemy)
{
	cout << endl;
	cout << TOP_BORDER << endl;
	cout << "�� ������ �������: " << endl;
	cout << "1. ������� �����" << endl;
	cout << "2. ������ �����" << endl;
	cout << "3. �������" << endl;
	cout << "4. �����" << endl; // ��� ������ �� �����, ��� ������ ���� �������
	// 5. ������� ���������. ����.: ������ �� �����
	cout << "8. ���������" << endl;
	cout << "9. ��������� ����" << endl;
	cout << "0. ����� �� ����" << endl;
	cout << "���� ��������: ";
	int userInput;
	cin >> userInput;
	cout << TOP_BORDER << endl;

	switch (userInput)
	{
	case 1:
		system("cls");
		player.BasicAttack(enemy);
		cout << TOP_BORDER << endl;
		return 1;
	case 2:
		// SpecialAttack()
		system("cls");
		cout << TOP_BORDER << endl;
		return 2;
	case 3:
		system("cls");
		player.Heal(8);
		cout << TOP_BORDER << endl;
		return 3;
	case 4:
		system("cls");
		cout << TOP_BORDER << endl;
		if (player.Flee(enemy))
		{
			return 4;
		}
		return 5;
	case 8:
		system("cls");
		cout << TOP_BORDER << endl;
		player.ShowInventory();
		return 8;
	case 9:
		system("cls");
		SaveGame(player, enemy);
		return 9;
	case 0:
		system("cls");
		cout << "�� ����� ������!" << endl;
		return 0;
	default:
		system("cls");
		cout << "������������ ���� �����������, ������: " << __LINE__ << " � �����: " << __FILE__ << endl;
		break;
	}
}

int EnemyTurnState::HandleAction(Character& player, Character& enemy)
{
	int enemyAction = rand() % 3;

	if (enemyAction == 0 && (double(enemy.health) / double(enemy.maxHealth)) * 100 >= 40)
	{
		enemy.BasicAttack(player);
		cout << endl;
		return 1;
	}
	else if (enemy.healthFlasks != 0 && (double(enemy.health) / double(enemy.maxHealth)) * 100 <= 40)
	{
		enemy.Heal(8);
		cout << endl;
		return 3;
	}

	// ���������� ����� ������������
	//						BattleActor (��� ������� � ���)
	//			EnemyActor					PlayerActor
	//	Pult					...
	int diceRoll = RollDice(20);
	if (diceRoll > enemy.uniqueAbilityDifficulty)
	{
		cout << "������, ��������� � ��� �������� ������� � ����� �� ��� � ������, ������� ������ ���������" << endl;
		enemy.minionSpawned = true;
	}
	/*else
	{
		if (enemy.Flee(player))
		{
			cout << enemy.name << " ������� � �����, �������� ���� ����� � ������ ������������..." << endl;
			return 4;
		}
		else return 5;
	}*/
}

void EnemyTurnState::HandleChangeState()
{
	context->SetBattleStateEnum(PlayerTurnEnum);
	this->context->TransitionToState(new PlayerTurnState);
}

// Реализация WinState
void WinState::HandleChangeState()
{
	// Будет реализовано позже
}

int WinState::HandleAction(Character& player, Character& enemy)
{
	// Будет реализовано позже
	return 0;
}

// Реализация LoseState
void LoseState::HandleChangeState()
{
	// Будет реализовано позже
}

int LoseState::HandleAction(Character& player, Character& enemy)
{
	// Будет реализовано позже
	return 0;
}
