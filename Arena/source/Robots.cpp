#include <Robots.hpp>
#include <RobotInfo.hpp>
#include <QDir>
#include <Sound.hpp>

Boxman* Robots::Avatar = NULL;

void Robots::populate(const std::vector<int> & botsType, const std::vector<int> & nbBots)
{
	QDir botsdir("./bots");
	botsdir.setFilter(QDir::Files);
	
	//reading of XMLFIle to load bots
	RobotInfo botInfo;	

	// chargement de toutes les AIs
	QFileInfoList botslist = botsdir.entryInfoList();
	for(int i=0;i<botslist.size();i++)
	{
		QFileInfo fileInfo = botslist.at(i);
		//if (fileInfo.fileName().endsWith(boxmanInfo.brain.c_str()))
		if(fileInfo.fileName().endsWith(".so"))
        {	
			std::cout << fileInfo.fileName().toStdString() << std::endl;
			void * plugin;
			// load a .so into memory  

			if(!(plugin = dlopen(fileInfo.absoluteFilePath().toStdString().c_str(), RTLD_NOW)))
				exit(EXIT_FAILURE);

			void * (*act)(kn::smashstein::Robot *);
			// resolve symbole act  
			if (!(act = (void* (*)(kn::smashstein::Robot *)) dlsym(plugin, "act")))
				exit(EXIT_FAILURE);

			void * (*init)();
			// resolve symbole init  
			if(!(init = (void* (*)()) dlsym(plugin, "init")))
				exit(EXIT_FAILURE);

			init();

			botsPlugins.push_back(std::pair< void *, std::vector<Boxman *> >(plugin,std::vector<Boxman *>()));
			
			std::string directory("bots/");
			directory.append(fileInfo.fileName().toStdString());
			pluginsName.push_back(directory);
			//std::cout << "create brain type " << directory << std::endl;
			
			botsPluginsAct.push_back(act);			
			// fin TEST
		}
	}
	
	// Creation des bots avec le plugin donné dans le xml 
	for(unsigned int i = 0 ; i < botsType.size(); ++i)
	{
		switch(botsType[i])
		{
			case BOXMAN:
				botInfo.init();
				botInfo.loadXML("data/boxman.xml");
				//printf("\n\tCREATE new BOXMAN %d ", botsType[i]);
			break;

			case BANDICOOT:
				botInfo.init();
				botInfo.loadXML("data/bandicoot.xml");
				//printf("\n\tCREATE new BANDICOOT %d ", botsType[i]);
			break;

			case HECTOR:
				botInfo.init();
				botInfo.loadXML("data/hector.xml");
				//printf("\n\tCREATE new HECTOR %d ", botsType[i]);
			break;
			
			case OPERA:
				botInfo.init();
				botInfo.loadXML("data/opera.xml");
				//printf("\n\tCREATE new OPERA %d ", botsType[i]);
			break;
		}
		
		unsigned int index = 0;
		bool found = false;
		while((index < pluginsName.size()) && !found)
		{
			//printf("compare brain %s and %s\n", pluginsName[index].c_str(), botInfo.brain.c_str());
			if(pluginsName[index] == botInfo.brain())
				found = true;
			else
				++index;
		}
		
		if(found)
			for(int j=0; j < nbBots[i]; ++j)
			{
				Boxman * bot = new Boxman(botInfo, botsType[i]);
				bot->id() = bots.size();
				//bot->id() = -1;
				bot->type() = botsType[i];

				// chargement des sons de l'animation du robot [SON]
				printf("animsounds all %d ",(int)Boxman::animSoundsAll.size());
				printf("type du bot actuel %d",bot->type());
				std::cout << "ABBA taille du vecteur Boxman::animSounds : " << Boxman::animSoundsAll[bot->type()-1].size() << std::endl; // (bot->type()-1)
				bot->animation.loadAnimationSounds( Boxman::animSoundsAll[bot->type()-1] ); // bot->type() à mettre ailleurs? mauvaise utilisation du static?

				bot->getRobotState().getPosition()[1] = 2.0;
				bot->getRobotState().getPosition()[0] = -2.0 + j;

				bots.push_back(bot);
				botsPlugins[index].second.push_back(bot);
			}
	}
}

void Robots::act()
{
	for (unsigned int i=0;i<botsPlugins.size();++i)
    {
		for (unsigned int j=0;j<botsPlugins[i].second.size();++j)
        {
			botsPluginsAct[i](botsPlugins[i].second[j]);
		}
	}
}


void Robots::unpopulate()
{
	for (unsigned int i=0;i<botsPlugins.size();++i)
    {
		/* resolve symbole destroy */
		void * (*destroy)();
		if(!(destroy = (void* (*)()) dlsym(botsPlugins[i].first, "destroy")))
			exit(EXIT_FAILURE);

		destroy();

		for(unsigned int j=0;j<botsPlugins[i].second.size();++j)
        {
			delete botsPlugins[i].second[j];
		}

		dlclose(botsPlugins[i].first);
	}
}

Boxman* Robots::getAvatar(int type)
{
	if(Avatar != NULL)
		delete Avatar;
		
	RobotInfo botInfo;
		
	switch(type)
	{
		case BOXMAN:
			botInfo.init();
			botInfo.loadXML("data/boxman.xml");
		break;
		
		case BANDICOOT:
			botInfo.init();
			botInfo.loadXML("data/bandicoot.xml");
		break;

		case HECTOR:
			botInfo.init();
			botInfo.loadXML("data/hector.xml");
		break;

		case OPERA:
			botInfo.init();
			botInfo.loadXML("data/opera.xml");
		break;
	}
	
	/*if(type == BANDICOOT)
		Avatar = new Boxman(botInfo, BANDICOOT);
	else if(type == BOXMAN)
		Avatar = new Boxman(botInfo, BOXMAN);
	else*/
		Avatar = new Boxman(botInfo, type);
		
	Avatar->id() = -1;
	Avatar->type() = type;

	Avatar->getRobotState().getPosition()[0] = botInfo.x();
	Avatar->getRobotState().getPosition()[1] = botInfo.y();
	Avatar->getRobotState().getPosition()[2] = botInfo.z();

	Avatar->getRobotState().getRotation()[0] = botInfo.xrot();
	Avatar->getRobotState().getRotation()[1] = botInfo.yrot();
	Avatar->getRobotState().getRotation()[2] = botInfo.zrot();

	Avatar->getRobotState().getScale() = botInfo.scale();

	Avatar->animation.loadAnimationTab(botInfo.anime().c_str());

	Avatar->animation.loadAnimationSounds( Boxman::animSoundsAll[Avatar->type()-1]); // Avatar->type() à mettre ailleurs? mauvaise utilisation du static?
	
	return Avatar;
}

void Robots::moveBot(const int & idBot, const unsigned int & sourcePlug, const unsigned int & targetPlug)
{
	if(sourcePlug > botsPlugins.size() || targetPlug > botsPlugins.size())
	   return ;
	   
	printf("######## MOVE Robot with id %d from IA %d to %d ########\n", idBot, sourcePlug, targetPlug);
		
	// searching of the bot in the plug bots list
	Boxman* botFound = NULL;
	
	bool found = false;
	unsigned int j=0;
	while(!found && j<botsPlugins[sourcePlug].second.size())
	{
		if(botsPlugins[sourcePlug].second[j]->id() == idBot)
		{
			botFound = botsPlugins[sourcePlug].second[j];
			found = true;
			
			// erasing of the bot
			botsPlugins[sourcePlug].second.erase(botsPlugins[sourcePlug].second.begin()+j);
		}
		else
			++j;
	}
	
	if(botFound != NULL)
	{
		botsPlugins[targetPlug].second.push_back(botFound);
	}
}
