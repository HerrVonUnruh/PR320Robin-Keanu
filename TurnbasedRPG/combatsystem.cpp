#include "combatsystem.h"
#include "entity.h"
#include "fightercomponent.h"
#include "InputComponent.h"
#include "component.h"
#include "uiDriver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

CombatSystem::CombatSystem()
	: _player(nullptr)
{

}

CombatSystem::~CombatSystem()
{
}

void CombatSystem::Init()
{
	std::srand(static_cast<unsigned int>(std::time(0)));


	std::unique_ptr<Entity> player = std::make_unique<Entity>();
	FighterComponent* playerFighterComponent = player->AddComponent<FighterComponent>();
	InputComponent* input = player->AddComponent<PlayerInputComponent>();
	input->SetCombatSystem(this);

	player->entityType = entityType::player;
	player->entitySubType = 0;

	playerFighterComponent->fighterStats = playerFighterComponent->defaultPlayerFighterStats;
	playerFighterComponent->currentweapon = playerFighterComponent->presetWeapons[2];

	_entities.push_back(std::move(player));
	_player = player.get();
}


void CombatSystem::Update(int &level)
{
	uiDriver uiDriver;

	
	if (_entities.size() == 1)
	{
		level++;

		std::vector<int> numbers;
		for (int i = 1; i <= 10; ++i) {
			numbers.push_back(i);
		}

		random_shuffle(numbers.begin(), numbers.end());

		int numEnemies = 2 + (rand() % 3);
		int* monsterIDS = new int[numEnemies];
		std::map<std::string, int>* enemyFighterStats = new std::map<std::string, int>[numEnemies];
		//Create enemies
		for (int i = 0; i < numEnemies; ++i)
		{
			std::unique_ptr<Entity> enemy = std::make_unique<Entity>();
			FighterComponent* enemyFighterComponent = enemy->AddComponent<FighterComponent>();
			InputComponent* input = enemy->AddComponent<AIInputComponent>();
			input->SetCombatSystem(this);

			enemy->entityType = entityType::enemy;
			enemy->entitySubType = numbers[i]; // HIER IST EIN KOMMIT FÜR KEANUUUUUUUUU
			monsterIDS[i] = enemy->entitySubType;

			enemyFighterComponent->fighterStats = enemyFighterComponent->defaultMonsterFighterStats[i + 4];
			enemyFighterComponent->currentweapon = enemyFighterComponent->presetWeapons[rand() % 3];
			enemyFighterStats[i] = enemyFighterComponent->fighterStats;

			_entities.push_back(std::move(enemy));
		}

		int lastMenuIndex = 0;
		int lasteMenuIndexOffset = 0;
		bool wasInMenu = false;

		uiDriver.drawTopLine();

		FighterComponent* playerFighterComponent = nullptr;
		for (int i = 0; i < _entities.size(); i++)
		{
			if (_entities[i].get()->entityType == entityType::player)
			{
				playerFighterComponent = _entities[i].get()->GetComponent<FighterComponent>();
				break;
			}
		}

		if (statPointsToSpend == 0)
		{
			statPointsToSpend = 5;
		}

		while (statPointsToSpend > 0)
		{
			std::map<std::string, int> fighterStats = playerFighterComponent->fighterStats;
			std::string* menuItems = new std::string[fighterStats.size() - 2];

			int lineAmount = 0;
			std::string* lines = uiDriver.generatePlayerStatsLines(fighterStats, lineAmount);

			std::map<std::string, std::string> nameStatMap;

			int index = 0;
			for (auto it = fighterStats.begin(); it != fighterStats.end(); ++it)
			{
				if (index >= 2)
				{
					menuItems[index - 2] = it->first.substr(7) + " (" + std::to_string(it->second) + ")";
					nameStatMap[menuItems[index - 2]] = it->first;
				}
				index++;
			}

			std::string pickedMenuItem = uiDriver.drawMenu(lines, lineAmount, "Give your player some more power (" + std::to_string(statPointsToSpend) + ") :", menuItems, fighterStats.size() - 2, lastMenuIndex, lasteMenuIndexOffset, wasInMenu);
			wasInMenu = true;
			delete[] menuItems;

			fighterStats.at(nameStatMap.at(pickedMenuItem)) = fighterStats.at(nameStatMap.at(pickedMenuItem)) + 1;

			playerFighterComponent->fighterStats = fighterStats;
			statPointsToSpend--;
		}




		bool hasPickedWeapon = false;
		playerFighterComponent->fighterStats.at("2_hide_MaxHitpoints") = playerFighterComponent->fighterStats.at("2_hide_MaxHitpoints") + (playerFighterComponent->fighterStats.at("6_hide_Constitution") * 4);

		if (playerFighterComponent->GetOwner().entitySubType == 1)
		{
			hasPickedWeapon = true;

			if ((rand() % 100) < 20)
			{
				playerFighterComponent->fighterStats.at("1_show_Hitpoints") = playerFighterComponent->fighterStats.at("2_hide_MaxHitpoints");
			}
		}
		else
		{
			playerFighterComponent->fighterStats.at("1_show_Hitpoints") = playerFighterComponent->fighterStats.at("2_hide_MaxHitpoints");
		}

		while (!hasPickedWeapon)
		{
			std::map<std::string, int> fighterStats = playerFighterComponent->fighterStats;

			int lineAmount = 0;
			std::string* lines = uiDriver.generatePlayerStatsLines(fighterStats, lineAmount);

			std::string* menuItems = new std::string[3];
			std::map<std::string, int> nameWeaponMap;


			for (int i = 0; i < 3; i++)
			{
				menuItems[i] = uiDriver.weapons[i];
				nameWeaponMap[menuItems[i]] = i;
			}

			int lastMenuIndex = 0;
			int lasteMenuIndexOffset = 0;
			std::string pickedMenuItem = uiDriver.drawMenu(lines, lineAmount, "Choose a Weapon :", menuItems, 3, lastMenuIndex, lasteMenuIndexOffset, wasInMenu);

			playerFighterComponent->currentweapon = playerFighterComponent->presetWeapons[nameWeaponMap.at(pickedMenuItem)];


			playerFighterComponent->GetOwner().entitySubType = 1;
			hasPickedWeapon = true;
		}
	}
	//std::cout << std::to_string(level) << std::endl;
	sortEntitiesByStat(_entities, "5_show_Initiative");

	int numEnemies = _entities.size() - 1;
	int* monsterIDS = new int[numEnemies];
	std::map<std::string, int>* enemyFighterStats = new std::map<std::string, int>[numEnemies];


	int ultracounter = 0;

	for (int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i]->entityType == entityType::enemy)
		{
			monsterIDS[ultracounter] = _entities[i]->entitySubType;
			enemyFighterStats[ultracounter] = _entities[i]->GetComponent<FighterComponent>()->fighterStats;
			ultracounter++;
		}
	}

	system("cls");
	uiDriver.drawTopLine();
	uiDriver.displayMonster(monsterIDS, numEnemies);
	uiDriver.displayMonsterStats(enemyFighterStats, numEnemies);
	uiDriver.drawCenterLine();


	for (int i = 0; i < _entities.size(); i++)
	{
		Entity* currentEntity = _entities[i].get();//->GetComponent<InputComponent>()->GetTarget();
		//combatManeuvers combatManeuver = _entities[i].get()->GetComponent<InputComponent>()->GetCombatManeuver();

		if (currentEntity->entityType == entityType::player)
		{
			FighterComponent *playerFighterComponent = currentEntity->GetComponent<FighterComponent>();

			if (playerFighterComponent->fighterStats.at("1_show_Hitpoints") < 0)
			{
				std::map<std::string, int> fighterStats = playerFighterComponent->fighterStats;

				int lineAmount = 0;
				std::string* lines = uiDriver.generatePlayerStatsLines(fighterStats, lineAmount);
				std::string menuItems[1] = { "ok" };
				int lastMenuIndex = 0;
				int lastMenuIndexOffset = 0;

				uiDriver.drawMenu(lines, lineAmount, "You died :", menuItems, 1, lastMenuIndex, lastMenuIndexOffset);


				gameOver = true;
				return;
			}
		}


		combatManeuvers pickedManeuver = currentEntity->GetComponent<InputComponent>()->GetCombatManeuver();
		int maneuverPenalty = 0;

		Entity* target;
		
		switch (pickedManeuver)
		{
		case standartAttack:
			target = currentEntity->GetComponent<InputComponent>()->GetTarget();


			if (canPerformAttack(currentEntity, target, maneuverPenalty))
			{
				calculateAndApplyDamage(currentEntity, target, true);
			}
			break;
		case sweepingStrike:
			maneuverPenalty = 4;

			for (int j = 0; j < _entities.size(); j++)
			{
				if (_entities[j].get() != currentEntity)
				{
					if (canPerformAttack(currentEntity, _entities[j].get(), maneuverPenalty))
					{
						calculateAndApplyDamage(currentEntity, _entities[j].get(), true);
					}
				}
			}
			break;
		case powerStrike:
			maneuverPenalty = 8;

			target = currentEntity->GetComponent<InputComponent>()->GetTarget();


			if (canPerformAttack(currentEntity, target, maneuverPenalty))
			{
				calculateAndApplyDamage(currentEntity, target, true, true);
			}
			break;
		default:
			break;
		}


		/*std::cout << static_cast<int>(combatManeuver) << std::endl;
		if (_entities[i].get()->entityType == entityType::player)
		{
			std::cout << uiDriver.getNameFromEnemy(currentEntity->entitySubType) << std::endl;

			//HIER STEHT EIN KOMMENTAR!!!!!!!!!!!!!!!!!!!!!!!!!!! <3
			//hier auch <3 -kc
			// hier steht ein weiterer Kommentar <3 RK
		}*/
	}

	for (int i = 0; i < _entities.size(); i++)
	{
		Entity* currentEntity = _entities[i].get();

		if (_entities[i].get()->entityType == entityType::player)
		{
			//std::cout << "der player pos: " + std::to_string(i) << std::endl;

			//std::cout << "der player lebt so: " + std::to_string(currentEntity->GetComponent<FighterComponent>()->fighterStats.at("1_show_Hitpoints")) << std::endl;
		}
	}
	//FightingLocig(entitunique ptr);
	// {
	//  create new List Sort by initiative 
	// if (initiative 1 == initivative 2)
	// {
	//      pick random wer zuerst dran ist.
	// }
	// 
	// loop über die sortierte Liste und mache jedes mal das jeweilige combatshitding
	// 
	// fightercomponent getTarget 
	// fightercomponent getcombatManeuver
	// 
	// combat menuver picken
	// Würfeln!
	// Rechnen
	// Combat Spieler + combat WaffeSpieler + 20Seitiges Würfelergebnis
	// Combat Gegnger + combat WaffeGegner + 20Seitiges Würfelergebnis
	// 
	// if ( Angreifer int - 8 powerstrike shit > Verteidger int)
	// {
	//  Berechne DMG
	//  Würfeln!
	// Würfel mit Würfel von Waffe
	// Ergebnis + Strength + weapon damage = potenzieller DMG
	// potenzieller DMG - Gegner Dexterity = wahrer DMG
	// Hitpoints Gegner - wahrer DMG.
	// 
	// if ( hitpoint == 0 )
	// {
	//  TOT()!
	// }
	// }
	//
	// Else
	// {
	//      block = 0DMG = Nischt!
	// }
	//
	// 
	// update();
	// 
	// 
	// 
	// }

	//Query input component and ask for target using GetComponent<InputComponent>()
	//Perform combat
	//Update IsGameOver
}

bool CombatSystem::canPerformAttack(Entity* entityAttacker, Entity* entityDefender, int maneuverCombatPenalty)
{
	FighterComponent* attackerFighterComponent = entityAttacker->GetComponent<FighterComponent>();
	FighterComponent* defenderFighterComponent = entityDefender->GetComponent<FighterComponent>();

	int attackerDiceRoll = (rand() % 19) + 1;
	int defenderDiceRoll = (rand() % 19) + 1;

	int attackerCombat = attackerFighterComponent->fighterStats.at("7_hide_Combat");
	int defenderCombat = defenderFighterComponent->fighterStats.at("7_hide_Combat");

	int attackerWeaponCombat = attackerFighterComponent->currentweapon.combat;
	int defenderWeaponCombat = defenderFighterComponent->currentweapon.combat;

	int attackerDefense = attackerDiceRoll + attackerCombat + attackerWeaponCombat;
	int defenderDefense = defenderDiceRoll + defenderCombat + defenderWeaponCombat;
	attackerDefense = attackerDefense - maneuverCombatPenalty;

	uiDriver uiDriver1;

	FighterComponent* playerFighterComponent = nullptr;
	for (int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i].get()->entityType == entityType::player)
		{
			playerFighterComponent = _entities[i].get()->GetComponent<FighterComponent>();
			break;
		}
	}

	if (attackerFighterComponent != playerFighterComponent)
	{
		std::map<std::string, int> fighterStats = playerFighterComponent->fighterStats;

		int lineAmount = 0;
		std::string* lines = uiDriver1.generatePlayerStatsLines(fighterStats, lineAmount);
		std::string menuItems[1] = { "ok" };
		int lastMenuIndex = 0;
		int lastMenuIndexOffset = 0;

		uiDriver1.drawMenu(lines, lineAmount, uiDriver1.getNameFromEnemy(entityAttacker->entitySubType) + " tries to Attack :", menuItems, 1, lastMenuIndex, lastMenuIndexOffset);
	}

	bool canPerform = attackerDefense > defenderDefense;

	return canPerform;
}



int CombatSystem::calculateAndApplyDamage(Entity* entityAttacker, Entity* forcedTargetEnity, bool forceTargetEnemy, bool doDoubleDamage)
{
	int returnValue = 0;

	InputComponent* inputComponentAttacker = entityAttacker->GetComponent<InputComponent>();

	Entity* entityDefender;

	if (!forcedTargetEnity)
	{
		entityDefender = inputComponentAttacker->GetTarget();
	}
	else
	{
		entityDefender = forcedTargetEnity;
	}

	FighterComponent* attackerFighterComponent = entityAttacker->GetComponent<FighterComponent>();
	FighterComponent* defenderFighterComponent = entityDefender->GetComponent<FighterComponent>();

	int weaponDiceRoll = 0;

	for (int i = 0; i < attackerFighterComponent->currentweapon.d6Amount; i++)
	{
		weaponDiceRoll += (rand() % 5) + 1;
	}

	int attackerStrenght = attackerFighterComponent->fighterStats.at("3_show_Strength");
	int weaponDamage = attackerFighterComponent->currentweapon.damage;
	int defenderDexterity = defenderFighterComponent->fighterStats.at("4_show_Dexterity");

	int potentialDamage = weaponDiceRoll + attackerStrenght + weaponDamage;
	int totalDamage = potentialDamage - defenderDexterity;

	if (totalDamage <= 0)
	{
		totalDamage = 0;
	}


	if (doDoubleDamage)
	{
		totalDamage = totalDamage * 2;
	}

	//std::cout << "                                                                              damage done:" + std::to_string(totalDamage) << std::endl;
	//std::cout << "                                                                              before attack life:" + std::to_string(defenderFighterComponent->fighterStats.at("1_show_Hitpoints")) << std::endl;

	uiDriver uiDriver1;

	FighterComponent* playerFighterComponent = nullptr;
	for (int i = 0; i < _entities.size(); i++)
	{
		if (_entities[i].get()->entityType == entityType::player)
		{
			playerFighterComponent = _entities[i].get()->GetComponent<FighterComponent>();
			break;
		}
	}

	std::map<std::string, int> fighterStats = playerFighterComponent->fighterStats;

	int lineAmount = 0;
	std::string* lines = uiDriver1.generatePlayerStatsLines(fighterStats, lineAmount);
	std::string menuItems[1] = { "ok" };
	int lastMenuIndex = 0;
	int lastMenuIndexOffset = 0;

	uiDriver1.drawMenu(lines, lineAmount, "Damage done " + std::to_string(totalDamage) + " :", menuItems, 1, lastMenuIndex, lastMenuIndexOffset);

	defenderFighterComponent->fighterStats.at("1_show_Hitpoints") = defenderFighterComponent->fighterStats.at("1_show_Hitpoints") - totalDamage;

	if (defenderFighterComponent->fighterStats.at("1_show_Hitpoints") < 0)
	{
		if (defenderFighterComponent != playerFighterComponent)
		{
			Entity& entity = defenderFighterComponent->GetOwner();

			auto it = std::find_if(_entities.begin(), _entities.end(), [&entity](const std::unique_ptr<Entity>& ptr) {
				return ptr.get() == &entity;
				});

			// Wenn das Element gefunden wurde, entfernen wir es
			if (it != _entities.end()) {
				_entities.erase(it);
			}

			returnValue++;
		}
	}
	return returnValue;
	//std::cout << "                                                                              after attack life:" + std::to_string(defenderFighterComponent->fighterStats.at("1_show_Hitpoints")) << std::endl;
};
