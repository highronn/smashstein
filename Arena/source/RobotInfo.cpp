#include <RobotInfo.hpp>

RobotInfo::RobotInfo():
brain_("bots/"), model_("md2/"), texture_("md2/"), anime_("md2/")
{}
		
RobotInfo::RobotInfo(std::string xmlFile):
brain_(""), model_("md2/"), texture_("md2/"), anime_("md2/")
{
	QDomDocument doc( "bot" );
	QFile file(xmlFile.c_str());
	
	// loading in memory of xml file
	file.open( QIODevice::ReadOnly );
	  
	doc.setContent( &file );
	
	file.close();
	
	QString affichage;
	QDomNodeList tab;
	QDomElement mesure, n;
	
	QDomElement racine = doc.documentElement();           //root marker
	QDomNode noeud = racine.firstChild();          // first marker
	
	while(!noeud.isNull())
	{
		mesure = noeud.toElement();

		if(mesure.tagName() == "name")
		{
			name_ = noeud.firstChild().toText().data().toStdString();
			//std::cout << "Bot name " << name_ << std::endl;
		}
		else if(mesure.tagName() == "brain")
		{
			brain_.append(noeud.firstChild().toText().data().toStdString());
			//std::cout << "Bot brain " << brain_ << std::endl;
		}
		else if (mesure.tagName() == "body")
		{		 
			velocity_  = (double)((mesure.attribute("velocity")).toFloat());
			//std::cout << "Bot velocity " << velocity_ << std::endl;

			resistance_  = (double)((mesure.attribute("resistance")).toFloat());
			//std::cout << "Bot resistance " << resistance_ << std::endl;
		  
			tab = mesure.childNodes();       //crée un tableau des enfants de « mesure »

			for(unsigned int i=0;i<tab.length();i++)
			{
				//pour chaque enfant, on extrait la donnée et on concatène
				n = tab.item(i).toElement();
				
				if(n.tagName() == "model")
				{
					x_ = (double)((n.attribute("x")).toFloat());
					//std::cout << " x = \"" << x_ << "\"";            //récupère l’attribut x

					y_ = (double)((n.attribute("y")).toFloat());
					//std::cout << " y = \"" << y_ << "\"";            //récupère l’attribut y

					z_ = (double)((n.attribute("z")).toFloat());
					//std::cout << " z = \"" << z_ << "\"";            //récupère l’attribut z

					xrot_ = (double)((n.attribute("xrot")).toFloat());
					//std::cout << " xrot = \"" << xrot_ << "\"";            //récupère l’attribut xrot

					yrot_ = (double)((n.attribute("yrot")).toFloat());
					//std::cout << " yrot = \"" << yrot_ << "\"";            //récupère l’attribut yrot

					zrot_ = (double)((n.attribute("zrot")).toFloat());
					//std::cout << " zrot = \"" << zrot_ << "\"";            //récupère l’attribut zrot

					scale_ = (double)((n.attribute("scale")).toFloat());
					//std::cout << " scale = \"" << scale_ << "\"";            //récupère l’attribut zrot					
					
					model_.append(tab.item(i).firstChild().toText().data().toStdString());
					//std::cout << "Bot model " << model_ << std::endl;
				}
				else if(n.tagName() == "texture")
				{
					texture_.append(tab.item(i).firstChild().toText().data().toStdString());
					//std::cout << "Bot texture " << texture_ << std::endl;
				}
				else if(n.tagName() == "anime")
				{
					anime_.append(tab.item(i).firstChild().toText().data().toStdString());
					//std::cout << "Bot anime " << anime_ << std::endl;
				}
			}
		}
	  
		noeud = noeud.nextSibling();
	}
}
		
RobotInfo::RobotInfo(const RobotInfo & r):
name_(r.name_), brain_(r.brain_), model_(r.model_), texture_(r.texture_), anime_(r.anime_),
x_(r.x_), y_(r.y_), z_(r.z_),
xrot_(r.xrot_), yrot_(r.yrot_), zrot_(r.zrot_)
{}

void RobotInfo::init()
{
	brain_ = "bots/";
	model_ = "md2/";
	texture_ = "md2/";
	anime_ = "md2/";
}

void RobotInfo::loadXML(std::string xmlFile)
{
	QDomDocument doc( "bot" );
	QFile file(xmlFile.c_str());
	
	// loading in memory of xml file
	file.open( QIODevice::ReadOnly );
	  
	doc.setContent( &file );
	
	file.close();
	
	QString affichage;
	QDomNodeList tab;
	QDomElement mesure, n;
	
	QDomElement racine = doc.documentElement();           //root marker
	QDomNode noeud = racine.firstChild();          // first marker
	
	while(!noeud.isNull())
	{
		mesure = noeud.toElement();

		if(mesure.tagName() == "name")
		{
			name_ = noeud.firstChild().toText().data().toStdString();
			//std::cout << "Bot name " << name_ << std::endl;
		}
		else if(mesure.tagName() == "brain")
		{
			brain_.append(noeud.firstChild().toText().data().toStdString());
			//std::cout << "Bot brain " << brain_ << std::endl;
		}
		else if (mesure.tagName() == "body")
		{		 
			velocity_  = (double)((mesure.attribute("velocity")).toFloat());
			//std::cout << "Bot velocity " << velocity_ << std::endl;

			resistance_  = (double)((mesure.attribute("resistance")).toFloat());
			//std::cout << "Bot resistance " << resistance_ << std::endl;
		  
			tab = mesure.childNodes();       //crée un tableau des enfants de « mesure »

			for(unsigned int i=0;i<tab.length();i++)
			{
				//pour chaque enfant, on extrait la donnée et on concatène
				n = tab.item(i).toElement();
				
				if(n.tagName() == "model")
				{
					x_ = (double)((n.attribute("x")).toFloat());
					//std::cout << " x = \"" << x_ << "\"";            //récupère l’attribut x

					y_ = (double)((n.attribute("y")).toFloat());
					//std::cout << " y = \"" << y_ << "\"";            //récupère l’attribut y

					z_ = (double)((n.attribute("z")).toFloat());
					//std::cout << " z = \"" << z_ << "\"";            //récupère l’attribut z

					xrot_ = (double)((n.attribute("xrot")).toFloat());
					//std::cout << " xrot = \"" << xrot_ << "\"";            //récupère l’attribut xrot

					yrot_ = (double)((n.attribute("yrot")).toFloat());
					//std::cout << " yrot = \"" << yrot_ << "\"";            //récupère l’attribut yrot

					zrot_ = (double)((n.attribute("zrot")).toFloat());
					//std::cout << " zrot = \"" << zrot_ << "\"";            //récupère l’attribut zrot

					scale_ = (double)((n.attribute("scale")).toFloat());
					//std::cout << " scale = \"" << scale_ << "\"";            //récupère l’attribut zrot					
					
					model_.append(tab.item(i).firstChild().toText().data().toStdString());
					//std::cout << "Bot model " << model_ << std::endl;
				}
				else if(n.tagName() == "texture")
				{
					texture_.append(tab.item(i).firstChild().toText().data().toStdString());
					//std::cout << "Bot texture " << texture_ << std::endl;
				}
				else if(n.tagName() == "anime")
				{
					anime_.append(tab.item(i).firstChild().toText().data().toStdString());
					//std::cout << "Bot anime " << anime_ << std::endl;
				}
			}
		}
	  
		noeud = noeud.nextSibling();
	}
}
