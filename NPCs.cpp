//struct Render_State {
//    int height, width;
//    void* memory;
//
//    BITMAPINFO bitmap_info;
//};


class NPC {

	public:

		float xlocation, ylocation;
		int level;
		void* memory;
		BITMAPINFO bitmap_info;

		int height, width;

		NPC (){
			this -> xlocation = xlocation;
			this -> ylocation = ylocation;
			this -> level = level;
		}


};


class Deamon : public NPC {

	public:

		float xlocation, ylocation;
		int level = 7;
		void* memory;
		BITMAPINFO bitmap_info;

		Deamon(){
			this -> xlocation = xlocation;
			this -> ylocation = ylocation;
			this -> level = level; 
		}

		void attack(){
			using std::endl;
			using std::cout;

			cout << "punching" << endl;
		}
};

class Angel : public NPC {

	

	public:
		

		float xlocation, ylocation;
		int level = 7;
		void* memory;
		BITMAPINFO bitmap_info;

		//float * xlocation, float * ylocation
		Angel(int level){
			this ->level = level;
		}

		void attack(){
			using std::endl;
			using std::cout;

			cout << "shooting"<< endl;
		}
};

class Render_State : public NPC {

	public:
		int height, width;
    	void* memory;

    	BITMAPINFO bitmap_info;
};