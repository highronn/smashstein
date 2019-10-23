#ifndef EDGEPROPERTYMAP_HPP
#define EDGEPROPERTYMAP_HPP

#include <boost/property_map.hpp>
#include <Edge.hpp>

class EdgeLengthMap : public boost::put_get_helper<float, EdgeLengthMap>
{
	public:
	  typedef float value_type;
	  typedef float& reference;
	  typedef Edge key_type;
	  typedef boost::readable_property_map_tag category;
	  reference operator[](key_type* a) const {return a->value();}
	  reference operator[](key_type& a) const {return a.value();}
};

#endif
