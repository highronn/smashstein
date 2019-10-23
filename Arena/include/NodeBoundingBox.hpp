#ifndef NODEBOUNDINGNBOX_HPP
#define NODEBOUNDINGNBOX_HPP

#include <boost/property_map.hpp>
#include <Node.hpp>

class NodeBoundingBox : public boost::put_get_helper<float, NodeBoundingBox>
{
	public:
	  typedef Node key_type;
	  typedef float value_type;
	  typedef value_type& reference;
	  typedef boost::readable_property_map_tag category;
	  //typedef boost::lvalue_property_map_tag category;
	  inline reference operator[](key_type & v) const {return v.x();}
};

/*template <typename KeyType, typename ValueType>
class ref_property_map :  public boost::put_get_helper<ValueType&,ref_property_map<KeyType,ValueType> >
{ 
  ValueType* value;
public:
  typedef KeyType key_type;
  typedef ValueType value_type;
  typedef ValueType& reference;
  typedef lvalue_property_map_tag category;
  ref_property_map(ValueType& v) : value(&v) {}
  ValueType& operator[](key_type const&) const { return *value; }

};*/

/*namespace detail {
    struct dummy_pmap_reference {
      template <class T>
      dummy_pmap_reference& operator=(const T&) { return *this; }
      operator int() { return 0; }
    };
  }
  class dummy_property_map 
    : public boost::put_get_helper<detail::dummy_pmap_reference,
        dummy_property_map  > 
  {
  public:
    typedef void key_type; 
    typedef int value_type;
    typedef detail::dummy_pmap_reference reference;
    typedef boost::read_write_property_map_tag category;
    inline dummy_property_map() : c(0) { }
    inline dummy_property_map(value_type cc) : c(cc) { }
    inline dummy_property_map(const dummy_property_map& x)
      : c(x.c) { }
    template <class Vertex>
    inline reference operator[](Vertex) const { return reference(); }
   protected:
    value_type c;
  };*/


#endif
