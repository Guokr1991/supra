// ================================================================================================
// 
// If not explicitly stated: Copyright (C) 2017, all rights reserved,
//      Rüdiger Göbl 
//		Email r.goebl@tum.de
//      Chair for Computer Aided Medical Procedures
//      Technische Universität München
//      Boltzmannstr. 3, 85748 Garching b. München, Germany
// 
// ================================================================================================

#include <utilities/Logging.h>

#include <SupraManager.h>

using namespace supra;

void quitCallback()
{
	SupraManager::Get()->stopAndWaitInputs();
}

int main(int argc, char** argv) {
	logging::Base::setLogLevel(logging::info);

	if (argc == 1)
	{
		logging::log_always("Usage: SUPRA_EXECUTOR <config.xml>");
	}
	else if (argc >= 2)
	{
		// general setup of the manager
		auto manager = SupraManager::Get();
		manager->setFreezeTimeout(36000);
		manager->setQuitCallback(quitCallback);

		// create and run the nodes
		manager->readFromXml(argv[1]);

		manager->startOutputs();
		manager->startInputs();

		// wait for all inputs to be finished
		manager->waitInputs();
		
		//wait for remaining messages to be processed
		manager->waitForGraph();
	}
}
