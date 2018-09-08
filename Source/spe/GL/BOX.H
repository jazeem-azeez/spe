# define false	0
# define true	1
struct Box
{
  point3d min,max;
};

inline float min(float a, float b)
{
  return (a < b ? a : b);
}

inline float max(float a, float b)
{
  return (a > b ? a : b);
}


// returns whether or not two boxes intersect
int intersect(const Box &b1, const Box &b2)
{
  if (b1.min.x > b2.max.x) return false;
  if (b2.min.x > b1.max.x) return false;

  if (b1.min.y > b2.max.y) return false;
  if (b2.min.y > b1.max.y) return false;

  if (b1.min.z > b2.max.z) return false;
  if (b2.min.z > b1.max.z) return false;

  return true;
}

// pre-condition: boxes must intersect
// returns the intersection of two boxes
Box isection(const Box &b1, const Box &b2)
{
  Box b3;
  b3.min.x = max(b1.min.x, b2.min.x);
  b3.max.x = min(b1.max.x, b2.max.x);

  b3.min.y = max(b1.min.y, b2.min.y);
  b3.max.y = min(b1.max.y, b2.max.y);

  b3.min.z = max(b1.min.z, b2.min.z);
  b3.max.z = min(b1.max.z, b2.max.z);

  return b3;
}

