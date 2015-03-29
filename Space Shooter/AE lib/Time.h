#ifndef __ATOMENGINE_TIME_LIBRARY_H__
# define __ATOMENGINE_TIME_LIBRARY_H__

/*
	A macro defined to export or import functions, variables, etc.
*/
# ifdef ATOMAPI
#  define ATOMAPI __declspec(dllexport)
# else
#  define ATOMAPI __declspec(dllimport)
# endif

namespace TimeLibrary {
	/* class that holds the time subsystem */
	class ATOMAPI Time {
	public:
		Time();
		~Time();

		float LocalElapsedTime();
		float LocalDeltaTime();
		void LocalReset();

		static float GetFPS();
		static float GetDeltaTime();
		static float GetElapsedTime();
		static void Reset();
	private:
		float previousTime;
		float presentTime;
		float startTime;

		float dt;
		float elapsedTime;
	protected:
	};
}

#endif