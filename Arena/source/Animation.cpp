#include <Animation.hpp>
#include <MD2Model.hpp>
#include <variables.hpp>

Animation::Animation():
anime(false), animeStartFrame(0), animeEndFrame(0), animeCurrentFrame(-1), 
fps_(30), animeInterFrameTime(0), animeType(ONE_SHOT), idAnime(-1), sounds()
{}

Animation::Animation(const Animation & a):
anime(a.anime), animeStartFrame(a.animeStartFrame), animeEndFrame(a.animeEndFrame), animeCurrentFrame(a.animeCurrentFrame), 
fps_(a.fps_), animeInterFrameTime(a.animeInterFrameTime), animeType(a.animeType), idAnime(a.idAnime), sounds()
{
	for(unsigned int i=0; i<a.animationTable.size(); ++i)
	{
		std::pair<int, int> p(a.animationTable[i].first, a.animationTable[i].second);
		animationTable.push_back(p);
	}
}

void Animation::animeModel(CMD2Model & m)
{
	int iMaxFrame = m.m_kHeader.num_frames - 1;
	//printf("\t ####### ANIME MODEL with %d frames ", iMaxFrame);
    if( (animeStartFrame < 0) || (animeEndFrame > iMaxFrame) )
        return;
    
    // look to know if the model was already animated
    if(animeType == ONE_SHOT && !anime && (animeCurrentFrame == -1))
		anime = true;
	else if(animeCurrentFrame == -1) // for LOOP animation
		anime = true;
		
	if(!anime)
	{
		//printf("in frame %d ###########\n", animeCurrentFrame);
		m.RenderFrame(animeCurrentFrame);
		return ;
	}
	//printf("anime model .... fps %d\n", fps_);
	// animation managing
	int time = TIMER.elapsed();
	
	if(animeCurrentFrame == -1)
	{
		animeCurrentFrame = animeStartFrame;
		animeInterFrameTime = time;

	}
	
	float frameTime = (1.0/(float)fps_) * 1000;
	float elapsedAnimeTime = (float)(time - animeInterFrameTime);
	
	//printf("anime frame %d frame time %.2f anime time %.2f\n", animeCurrentFrame, frameTime, elapsedAnimeTime);
	
	if(elapsedAnimeTime >= frameTime)
	{
		// calcul du coefficient pour sauter les frames qui aurait déjà du etre jouée
		int coeff = round(elapsedAnimeTime / frameTime);
		animeCurrentFrame += coeff;
		
		animeInterFrameTime = time;
		
		if(animeCurrentFrame > animeEndFrame)
		{
			switch(animeType)
			{
				case LOOP:
					animeCurrentFrame = animeStartFrame;
				break;
				
				case ONE_SHOT:
					animeCurrentFrame = animeEndFrame;
					anime = false;
				break;
			}
		}
	}
	//printf("in frame %d ###########\n", animeCurrentFrame);
	m.RenderFrame(animeCurrentFrame);
}

void Animation::loadAnimationTab(const char* path)
{
	std::ifstream file(path, std::ios::in);
	std::string line;
	std::istringstream readBuffer;
	//printf("load anime Table from %s\n", path);

	while(std::getline(file, line))
	{
		readBuffer.clear();
		readBuffer.str(line);
		
		if((line[0] >= '1') && (line[0] <= '9'))
		{
			int idAnime, start, end;
			
			readBuffer >> idAnime;
			readBuffer >> start;
			readBuffer >> end;
			
			//std::cout << "ANIME " << idAnime << " -> " << "(" << start << "," << " " <<  end << ")" << std::endl;
			
			std::pair<int, int> p(start, end);
			animationTable.push_back(p);
		}
	}
	
	file.close();
}

void Animation::setAnimation(int type, int fps)
{
	if((type <= 0) || (type > NB_ANIM) || (fps < 0))
		return;
	
	if(idAnime != type)
	{
		idAnime = type;
		animeInterFrameTime = TIMER.elapsed();
		animeCurrentFrame = -1;
		animeStartFrame = animationTable[type-1].first;
		animeEndFrame = animationTable[type-1].second;
		fps_ = fps;
		
		//printf("set anim %d %d %d vitesse %d\n", type, animationTable[type].first, animationTable[type].second, fps_);

		// [TEST SON]
		//printf("test : jouer un son lors de l'anim\n");
		if(type <= (int)sounds.size())
		{
			if(sounds[type-1] != NULL)
			{
				sounds[type-1]->play();
				sounds[type-1]->setVolume(0.1f);
				//printf("test son ok\n");
			}
			else
				printf("echec du test (1) : sounds[%d] est NULL\n", type-1);
		}
		else if(sounds[1] != NULL)
		{
			sounds[1]->play();
			//printf("test son ok mais son par défaut joué.\n");
		}
		else
			printf("echec du test son\n");
		// -------- fin test son.
	}
}

void Animation::loadAnimationSounds(std::vector<Sound*> & importedSounds)
{
	//printf("loadAnimationSounds\n");
	//std::cout << "sounds.size() = " << sounds.size() << std::endl;
	for(unsigned int i = 0; i<importedSounds.size(); i++)
	{
		sounds.push_back(importedSounds[i]);
	}
	
	//printf("loadAnimationSounds ok\n");
}

bool Animation::isTerminate()
{
	if(animeType == LOOP)
		return true;
	else if(animeType == ONE_SHOT)
	{
		if(animeCurrentFrame == animeEndFrame)
			return true;
		else 
			return false;
	}
	else return true;
}

