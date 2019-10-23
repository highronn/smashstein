#include "../include/main.hpp"
#include "../include/variables.hpp"

int main(int argc, char** argv)
{
	QApplication a( argc, argv );
	
	QDomDocument doc( "DumbBot" );
	QFile file( XML_FILE );
	
	// loading in memory of xml file
	if( !file.open( QIODevice::ReadOnly ) )
		return -1;
	  
	if( !doc.setContent( &file ) )
	{
		file.close();
		return -2;
	}
	
	file.close();
	
	// looking for the root
	QDomElement root = doc.documentElement();
	
	if( root.tagName() != "bot" )
		return -3;
		
	// reading of dom structure
	QDomNode n = root.firstChild();
	while( !n.isNull() )
	{
		QDomElement e = n.toElement();
		if( !e.isNull() )
		{
			if( e.tagName() == "name" )
			{
				printf("name found\n");
				/*Contact c;

				c.name = e.attribute( "name", "" );
				c.phone = e.attribute( "phone", "" );
				c.eMail = e.attribute( "email", "" );*/
			}
			else if( e.tagName() == "brain" )
			{
				printf("brain found\n");
			}
			else if( e.tagName() == "body" )
			{
				printf("body found\n");
			}			
		}

		n = n.nextSibling();
	}
	
	std::cout << "OK" << std::endl;
	
	return EXIT_SUCCESS;
}
