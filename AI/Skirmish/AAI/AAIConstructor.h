// -------------------------------------------------------------------------
// AAI
//
// A skirmish AI for the Spring engine.
// Copyright Alexander Seizinger
//
// Released under GPL license: see LICENSE.html for more information.
// -------------------------------------------------------------------------

#ifndef AAI_CONSTRUCTOR_H
#define AAI_CONSTRUCTOR_H

#include "aidef.h"

class AAI;
class AAIBuildTable;
class AAIBuildTask;

#include <list>
using namespace std;

class AAIConstructor
{
public:
	AAIConstructor(AAI *ai, int unit_id, int def_id, bool factory, bool builder, bool assistant);
	~AAIConstructor(void);

	void Update();

	void Idle();

	// checks if assisting builders needed
	void CheckAssistance();


	// stops all assisters from assisting this unit
	void ReleaseAllAssistants();
	// stops this unit from assisting another builder/factory
	void StopAssisting();

	void ConstructionFinished();
	void ConstructionFailed();
	void GiveConstructionOrder(int id_building, float3 pos, bool water);
	void AssistConstruction(int constructor, int target_unit = -1);
	// continue with construction after original builder has been killed
	void TakeOverConstruction(AAIBuildTask *build_task);

	void GiveReclaimOrder(int unit_id);

	void Killed();

	// moves mobile constructors to safe sectors
	void Retreat(UnitCategory attacked_by);


	// specify type of construction units (several values may be true, e.g. builders that may build certain combat units as well)
	bool factory;		// can build units
	bool builder;		// can build buildings
	bool assistant;		// can assists construction (nanotowers, fark, etc.)

	// ids of the construction unit
	int unit_id;
	int def_id;
	int buildspeed;

	// ids of the currently constructed unit/building (-1 if none)
	int construction_def_id;
	int construction_unit_id;
	UnitCategory construction_category;
	// current task (idle, building, assisting)
	UnitTask task;

	// zero vector if none
	float3 build_pos;
	// id of the unit, the builder currently assists (-1 if none)
	int assistance;
	// assistant builders
	set<int> assistants;

	// pointer to possible buildtask
	AAIBuildTask *build_task;
private:
	// removes an assisting con unit
	void RemoveAssitant(int unit_id);
	// gets the total buildtime of all units in the buildque of the factory
	double GetMyQueBuildtime();
	bool IsBusy();

//	bool resurrect;		// can resurrect
	AAI *ai;
	// engine tick the build order had been given
	int order_tick;
	// buildque
	list<int> *buildque;

};

#endif

