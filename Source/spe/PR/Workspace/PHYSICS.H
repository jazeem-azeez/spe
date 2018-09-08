

#if !defined(PHYSICS_H)
#define PHYSICS_H



/*----------------------------------------------------------------------------

Declarations for physics code.

*/

struct rigid_body
{
	real Width, Height;
	real OneOverMass, OneOverCMMomentOfInertia;
	real CoefficientOfRestitution;

	enum { NumberOfConfigurations = 2 };

	struct configuration
	{
		vector_2 CMPosition;
		real Orientation;

		vector_2 CMVelocity;
		real AngularVelocity;

		vector_2 CMForce;
		real Torque;

		struct bounding_box
		{
			vector_2 aVertices[4];

		} BoundingBox;

	} aConfigurations[NumberOfConfigurations];
};

class simulation_world
{
public:

	simulation_world( real WorldWidth, real WorldHeight );

	void Simulate( real DeltaTime );
	void Render( void );
	
	~simulation_world( void );

private:

	enum collision_state
	{
		Penetrating,
		Colliding,
		Clear
	} CollisionState;

	vector_2 CollisionNormal;
	int CollidingBodyIndex;
	int CollidingCornerIndex;

	int SourceConfigurationIndex;
	int TargetConfigurationIndex;

	void ComputeForces( int ConfigurationIndex );
	void Integrate( real DeltaTime );
	collision_state CheckForCollisions( int ConfigurationIndex );
	void ResolveCollisions( int ConfigurationIndex );
	void CalculateVertices( int ConfigurationIndex );

	real WorldWidth, WorldHeight;

	enum { NumberOfWalls = 5 };
	struct wall
	{
		// define wall by plane equation
		vector_2 Normal;		// inward pointing
		real c;					// ax + by + c = 0

		// points for drawing wall
		vector_2 StartPoint;
		vector_2 EndPoint;
	} aWalls[NumberOfWalls];

	enum { NumberOfBodies = 2 };
	rigid_body aBodies[NumberOfBodies];
};

#endif
