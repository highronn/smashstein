#ifndef ROBOTINFO_HPP
#define ROBOTINFO_HPP

#include <iostream>
#include <string>

#include <QtGui/QApplication>
#include <QObject>
#include <Qt/qgl.h>
#include <QtGui/QtGui>

#include <QDomDocument>
#include <QFile>

class RobotInfo
{
	private :
		std::string name_;
		std::string brain_;
		
		std::string model_;
		std::string texture_;
		std::string anime_;
		
		float velocity_, resistance_;
		float x_, y_, z_;
		float xrot_, yrot_, zrot_;
		float scale_;
		
	public :
		RobotInfo();
		RobotInfo(std::string xmlFile);
		RobotInfo(const RobotInfo &);
		~RobotInfo() {}
		
	public :
		inline const std::string & name() const {return name_;}
		inline std::string & name() {return name_;}
		
		inline const std::string & brain() const {return brain_;}
		inline std::string & brain() {return brain_;}
		
		inline const std::string & model() const {return model_;}
		inline std::string & model() {return model_;}
		
		inline const std::string & texture() const {return texture_;}
		inline std::string & texture() {return texture_;}
		
		inline const std::string & anime() const {return anime_;}
		inline std::string & anime() {return anime_;}
		
		inline const float & velocity() const {return velocity_;}
		inline float & velocity() {return velocity_;}
		
		inline const float & resistance() const {return resistance_;}
		inline float & resistance() {return resistance_;}
		
		inline const float & x() const {return x_;}
		inline float & x() {return x_;}
		
		inline const float & y() const {return y_;}
		inline float & y() {return y_;}
		
		inline const float & z() const {return z_;}
		inline float & z() {return z_;}
		
		inline const float & xrot() const {return xrot_;}
		inline float & xrot() {return xrot_;}
		
		inline const float & yrot() const {return yrot_;}
		inline float & yrot() {return yrot_;}
		
		inline const float & zrot() const {return zrot_;}
		inline float & zrot() {return zrot_;}
		
		inline const float & scale() const {return scale_;}
		inline float & scale() {return scale_;}
		
		void init();
		void loadXML(std::string xmlFile);
};

#endif
