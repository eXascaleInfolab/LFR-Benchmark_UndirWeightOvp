





class Parameters {
	
	
	public:
	
		Parameters();
		
		~Parameters(){};
		
		int num_nodes;
		double average_k;
		int max_degree;
		double tau;
		double tau2;
		double mixing_parameter;
		double mixing_parameter2;
		double beta;
		int overlapping_nodes;
		int overlap_membership;
		int nmin;
		int nmax;
		bool fixed_range;
		bool excess;
		bool defect;
		bool randomf;
		double clustering_coeff;
		bool directed;  // Directed network (arcs) or undirected (edges)

		bool cnodes;  // List communities as string of nodes per each community (such format is used in NMI evaluation)
		// Output data filenames
		string fnameNetwork;
		string fnameCommunity;
		string fnameStatistics;
		string fnameSeed;
		
		
		bool set(string &, string &);
		void set_random();
		bool arrange();
		deque<string> command_flags;
	
	



};

Parameters::Parameters() {
			
			
		num_nodes=unlikely;
		average_k=unlikely;
		max_degree=unlikely;
		
		tau=2;
		tau2=1;
		
		mixing_parameter=unlikely;
		mixing_parameter2=unlikely;
		
		beta=1.5;
		
		overlapping_nodes=0;
		overlap_membership=0;
		
		nmin=unlikely;
		nmax=unlikely;
		
		randomf=false;
		fixed_range=false;
		excess=false;
		defect=false;

		clustering_coeff=unlikely;
		
		directed = false;
		cnodes = false;
		
		fnameNetwork = "network.dat";
		fnameCommunity = "community.dat";
		fnameStatistics = "statistics.dat";
		fnameSeed = "seed.txt";


		command_flags.push_back("-N");			//0
		command_flags.push_back("-k");			//1
		command_flags.push_back("-maxk");		//2
		command_flags.push_back("-mut");		//3
		command_flags.push_back("-t1");			//4
		command_flags.push_back("-t2");			//5
		command_flags.push_back("-minc");		//6
		command_flags.push_back("-maxc");		//7
		command_flags.push_back("-on");			//8
		command_flags.push_back("-om");			//9
		command_flags.push_back("-beta");		//10
		command_flags.push_back("-muw");		//11
		command_flags.push_back("-C");			//12
		command_flags.push_back("-cnl");		//13
		command_flags.push_back("-a");			//14
		command_flags.push_back("-name");		//15
		command_flags.push_back("-seed");		//16
			
		
};


void Parameters::set_random() {


	cout<<"this is a random network"<<endl;
	mixing_parameter=0;
	mixing_parameter2=0;
	overlapping_nodes=0;
	overlap_membership=0;
	nmax=num_nodes;
	nmin=num_nodes;
	
	
	fixed_range=true;
	excess=false;
	defect=false;

}


bool Parameters::arrange() {
		
		
	if(randomf)
		set_random();
	
	
	
	if (num_nodes==unlikely) {
	
		cerr<<"\n***********************\nERROR:\t number of nodes unspecified"<<endl;
		return false;
	
	}
	if (average_k==unlikely) {
	
		cerr<<"\n***********************\nERROR:\t average degree unspecified"<<endl;
		return false;
	
	}
	
	if (max_degree==unlikely) {
	
		cerr<<"\n***********************\nERROR:\t maximum degree unspecified"<<endl;
		return false;
	
	}
	
	if (mixing_parameter2==unlikely) {
	
		cerr<<"\n***********************\nERROR:\t weight mixing parameter (option -muw) unspecified"<<endl;
		return false;
	
	}
	
	
	if(mixing_parameter==unlikely)
		mixing_parameter=mixing_parameter2;
	
	
	if(overlapping_nodes<0 || overlap_membership<0) {
	
		cerr<<"\n***********************\nERROR:\tsome positive parameters are negative"<<endl;
		
		return -1;

	
	}
		
	if (num_nodes<=0 || average_k<=0 || max_degree<=0 || mixing_parameter<0 || mixing_parameter2<0 || (nmax<=0 && nmax!=unlikely) || (nmin<=0 && nmin!=unlikely) ) {
	
		cerr<<"\n***********************\nERROR:\tsome positive parameters are negative"<<endl;
		
		return -1;

	
	}
	
	if(mixing_parameter > 1 || mixing_parameter2 > 1) {
	
		cerr<<"\n***********************\nERROR:\tmixing parameter > 1 (must be between 0 and 1)"<<endl;
		
		return -1;

	
	}
	
	
			
	if(nmax!= unlikely && nmin!=unlikely)
		fixed_range=true;
	else
		fixed_range=false;
		
		
	if(excess && defect) {
		
		cerr<<"\n***********************\nERROR:\tboth options -inf and -sup cannot be used at the same time"<<endl;
		return false;
	
	}


	
	
	
	cout<<"\n**************************************************************"<<endl;
	cout<<"network:\t"<<fnameNetwork<<endl;
	cout<<"number of nodes:\t"<<num_nodes<<endl;
	cout<<"average degree:\t"<<average_k<<endl;
	cout<<"maximum degree:\t"<<max_degree<<endl;
	cout<<"exponent for the degree distribution:\t"<<tau<<endl;
	cout<<"exponent for the community size distribution:\t"<<tau2<<endl;
	cout<<"mixing parameter(topology):\t"<<mixing_parameter<<endl;
	cout<<"mixing parameter (weights):\t"<<mixing_parameter2<<endl;
	cout<<"beta exponent:\t"<<beta<<endl;
	cout<<"number of overlapping nodes:\t"<<overlapping_nodes<<endl;
	cout<<"number of memberships of the overlapping nodes:\t"<<overlap_membership<<endl;
	cout<<"compact communities output format (NMI eval compatible):\t"<<cnodes<<endl;
	if(clustering_coeff!=unlikely)
		cout<<"Average clustering coefficient: "<<clustering_coeff<<endl;
	
	
	if (fixed_range) {
		cout<<"community size range set equal to ["<<nmin<<" , "<<nmax<<"]"<<endl;
		
		if (nmin>nmax) {
			cerr<<"\n***********************\nERROR: INVERTED COMMUNITY SIZE BOUNDS"<<endl;
			return false;
		}
		
		if(nmax>num_nodes) {
			cerr<<"\n***********************\nERROR: maxc BIGGER THAN THE NUMBER OF NODES"<<endl;
			return false;
		}
			
		
	
	}
	cout<<"**************************************************************"<<endl<<endl;
		
	


	



	return true;


}


bool Parameters::set(string & flag, string & num) {

	// false is something goes wrong
	
	
	
	cout<<"setting... "<<flag<<" "<<num<<endl;
	double err;
	if(flag != command_flags[15] && flag != command_flags[16]
	&& !cast_string_to_double(num, err)) {
				
		cerr<<"\n***********************\nERROR while reading parameters (floating point cast failed)"<<endl;
		return false;
			
	}	
		
	if (flag==command_flags[0]) {			
				
		if (fabs(err-int (err))>1e-8) {
				
			cerr<<"\n***********************\nERROR: number of nodes must be an integer"<<endl;
			return false;
			
		}
		
		num_nodes=cast_int(err);
			
			
	}
	else if(flag==command_flags[1]) {
		
		average_k=err;
	
	}
	else if(flag==command_flags[2]) {
		
		max_degree=cast_int(err);
	
	}
	else if(flag==command_flags[3]) {
		
		mixing_parameter=err;
	
	}
	else if(flag==command_flags[11]) {
		
		mixing_parameter2=err;
	
	}
	else if(flag==command_flags[10]) {
		
		beta=err;
	
	}
	else if(flag==command_flags[4]) {
		
		tau=err;
	
	}
	else if(flag==command_flags[5]) {
		
		tau2=err;
	
	}
	
	else if(flag==command_flags[6]) {
					
		if (fabs(err-int (err))>1e-8) {
						
			cerr<<"\n***********************\nERROR: the minumum community size must be an integer"<<endl;
			return false;
					
		}
					
		nmin=cast_int(err);

	}
	
	else if(flag==command_flags[7]) {
					
		if (fabs(err-int (err))>1e-8) {
						
			cerr<<"\n***********************\nERROR: the maximum community size must be an integer"<<endl;
			return false;
					
		}
					
		nmax=cast_int(err);

	}
	else if(flag==command_flags[8]) {
					
		if (fabs(err-int (err))>1e-8) {
						
			cerr<<"\n***********************\nERROR: the number of overlapping nodes must be an integer"<<endl;
			return false;
					
		}
					
		overlapping_nodes=cast_int(err);

	}
	else if(flag==command_flags[9]) {
					
		if (fabs(err-int (err))>1e-8) {
						
			cerr<<"\n***********************\nERROR: the number of membership of the overlapping nodes must be an integer"<<endl;
			return false;
					
		}
					
		overlap_membership=cast_int(err);

	}
	else if(flag==command_flags[12]) {
					
		clustering_coeff=err;		

	}
	else if(flag==command_flags[13]) {
		cnodes=cast_int(err);
		if(cnodes && fnameCommunity.find(".nmc", fnameCommunity.size() - 4) != string::npos)
			fnameCommunity.replace(fnameCommunity.size() - 4, 4, ".cnl");
	}
	else if(flag==command_flags[14]) {
		directed=cast_int(err);
		string  ext = directed ? ".nsa" : ".nse";
		size_t  iext = fnameNetwork.rfind('.');
		if(iext != string::npos && fnameNetwork.substr(iext) != ext) {
			fnameNetwork.resize(iext);
			fnameNetwork += ext;
		}
	}
	else if(flag==command_flags[15]) {
		fnameNetwork = fnameCommunity = fnameStatistics = num;
		fnameNetwork += directed ? ".nsa" : ".nse";  // Network, represented by tab separated arcs
		if(cnodes)
			fnameCommunity += ".cnl";  // Communities nodes lists / Nodes membership in communities
		else fnameCommunity += ".nmc";  // Communities nodes lists / Nodes membership in communities
		fnameStatistics += ".nst";  // Network statistics
	}
	else if(flag==command_flags[16]) {
		fnameSeed = num;
	}
	else {
				
		cerr<<"\n***********************\nERROR while reading parameters: "<<flag<<" is an unknown option"<<endl;
		return false;
			
	}
	
	
	
	return true;
	


}




void statement() {
	
	cout<<"\nTo run the program type \n./benchmark [FLAG] [P]"<<endl;
	
	cout<<"\n----------------------\n"<<endl;
	cout<<"To set the parameters, type:"<<endl<<endl;
	
	cout<<"-N\t\t[number of nodes]"<<endl;
	cout<<"-k\t\t[average degree]"<<endl;
	cout<<"-maxk\t\t[maximum degree]"<<endl;
	cout<<"-mut\t\t[mixing parameter for the topology]"<<endl;	
	cout<<"-muw\t\t[mixing parameter for the weights]"<<endl;	
	cout<<"-beta\t\t[exponent for the weight distribution]"<<endl;	
	cout<<"-t1\t\t[minus exponent for the degree sequence]"<<endl;
	cout<<"-t2\t\t[minus exponent for the community size distribution]"<<endl;
	cout<<"-minc\t\t[minimum for the community sizes]"<<endl;
	cout<<"-maxc\t\t[maximum for the community sizes]"<<endl;
	cout<<"-on\t\t[number of overlapping nodes]"<<endl;
	cout<<"-om\t\t[number of memberships of the overlapping nodes]"<<endl;
	cout<<"-C\t\t[Average clustering coefficient]"<<endl;
	cout<<"-cnl\t\t[output communities as strings of nodes (input format for NMI evaluation)]"<<endl;
	cout<<"-name\t\t[base name for the output files]. It is used for the network, communities"
		" and statistics; files extensions are added automatically:\n"
		"\t.nsa  - network, represented by space/tab separated arcs\n"
		"\t.nse  - network, represented by space/tab separated edges\n"
		"\t{.cnl, .nmc}  - communities, represented by nodes lists '.cnl' if '-cnl' is used"
			", otherwise as a nodes membership in communities '.nmc')\n"
		"\t.nst  - network statistics\n";
	cout<<"-seed\t\t[file name of the random seed, default: seed.txt]\n";
	cout<<"-a\t\t[{0, 1} yield directed network (1 - arcs) rather than undirected (0 - edges), default: 0 - edges]\n";


	cout<<"\n----------------------\n"<<endl;
	cout<<"It is also possible to set the parameters writing flags and relative numbers in a file. To specify the file, use the option:"<<endl;
	cout<<"-f\t[filename]"<<endl;
	cout<<"You can set the parameters both writing some of them in the file, and using flags from the command line for others."<<endl<<endl;
	cout<<"-N, -k, -maxk, -muw have to be specified. For the others, the program can use default values:"<<endl;
	cout<<"t1=2, t2=1, on=0, om=0, beta=1.5, mut=muw, minc and maxc will be chosen close to the degree sequence extremes."<<endl;
	cout<<"If you don't specify -C the rewiring process for raising the average clustering coefficient will not be performed"<<endl;
	cout<<"If you set a parameter twice, the latter one will be taken."<<endl;
	
	cout<<"\n-------------------- Other options ---------------------------\n"<<endl;
	
	
	cout<<"To have a random network use:"<<endl;
	cout<<"-rand"<<endl;
	cout<<"Using this option will set muw=0, mut=0, and minc=maxc=N, i.e. there will be one only community."<<endl;
	
		
	
	cout<<"Use option -sup (-inf) if you want to produce a benchmark whose distribution of the ratio of external degree/total degree ";
	cout<<"is superiorly (inferiorly) bounded by the mixing parameter."<<endl;

	cout<<"\n-------------------- Examples ---------------------------\n"<<endl;
	cout<<"Example1:"<<endl;
	cout<<"./benchmark -N 1000 -k 15 -maxk 50 -muw 0.1 -minc 20 -maxc 50 -cnl 1 -name gen/case1K15"<<endl;
	cout<<"Example2:"<<endl;
	cout<<"./benchmark -f flags.dat -t1 3"<<endl;
	
	cout<<"\n-------------------- Other info ---------------------------\n"<<endl;
	cout<<"Read file ReadMe.txt for more info."<<endl<<endl;
	
	
}


bool set_from_file(string & file_name, Parameters & par1) {


	int h= file_name.size();
	char b[h+1];
	cast_string_to_char(file_name, b);
	
	ifstream in(b);
	if (!in.is_open()) {
		cerr<<"File "<<file_name<<" not found. Where is it?"<<endl;
		return false;
	}
	
	
	
	string temp;
	while(in>>temp) {			// input file name

		
		if(temp=="-rand")
			par1.randomf=true;
		
		else if(temp=="-sup")
			par1.excess=true;
		
		else if(temp=="-inf")
			par1.defect=true;
		
		else {
			
				
			string temp2;
			in>>temp2;
			
			
			if(temp2.size()>0) {
			
				
				if(temp=="-f" && temp2 != file_name) {
					if(set_from_file(temp2, par1)==false)
						return false;
				}
				
				if(temp!="-f") {
					if(par1.set(temp, temp2)==false)
						return false;
				}
			
			
			}
		
			else {
			
				cerr<<"\n***********************\nERROR while reading parameters set_from_file()"<<endl;
				return false;
		
			}
		}
		
	}

	
	return true;
	

}



bool set_parameters(int argc, char * argv[], Parameters & par1) {
	
	int argct = 0;
	string temp;
	
	if (argc <= 1) { // if no arguments, return statement about program usage.
		
		statement();
		return false;
	}



		
	while (++argct < argc) {			// input file name

		temp = argv[argct];
		
		
		if(temp=="-rand")
			par1.randomf=true;
		
		
		else if(temp=="-sup")
			par1.excess=true;
		
		else if(temp=="-inf")
			par1.defect=true;
		
		else {
			
			argct++;
				
			string temp2;
				
			if(argct<argc) {
			
				temp2 = argv[argct];
				

				if(temp=="-f") {
					
					if(set_from_file(temp2, par1)==false)
						return false;
					
				}
				

				
				if(temp!="-f") {
					
					
					if(par1.set(temp, temp2)==false)
						return false;
						
						
				}
				
			}
		
			else {
			
				cerr<<"\n***********************\nERROR while reading parameters set_parameters(), arg: "
					<< temp << endl;
				return false;
		
			}
		}
		
	}
	
	
	if(par1.arrange()==false)
		return false;
	
	return true;
}




