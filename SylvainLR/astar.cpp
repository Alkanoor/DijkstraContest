#include <vector>
#include <stdio.h>
#include <math.h>

//attention, j'ai mis tous les delete (3 au total) en commentaire

const int m=5;//longueur de la carte
const int n=5;//largeur de la carte
static int carte[n][m];
static int closed_nodes_map[n][m]; // map of closed (tried-out) nodes
static int open_nodes_map[n][m]; // map of open (not-yet-tried) nodes
static int dir_map[n][m]; // map of directions
const int dir=4; // number of possible directions to go at any position
static int dx[dir]={0, 1, 0, -1};
static int dy[dir]={1, 0, -1, 0};
int xStart=1;
int yStart=1;
int xFinish = 3;
int yFinish = 3;
int j;
int x=0;
int y=0;
//String route="";
int fin = 1;
int recherche = 1;
/*état des noeuds :
0 = inexploré
1 = occupé
2 = libre*/

//création de la classe noeud
class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        node(int xp, int yp, int d, int p) 
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest); //A*
        }

        void nextLevel ()
        {
             level+=1;
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // Euclidian Distance
            d=static_cast<int>(sqrt(xd*xd+yd*yd));
        
            return(d);
        }
};




/*  // Determine priority (in the priority queue)
  boolean operator<(const node & a, const node & b)
  {
    return a.getPriority() > b.getPriority();
  }*/
  

// A-star algorithm.
// The route returned is a string of direction digits.
void pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish )
{
    
    std::vector<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static int i, j, x, y, xdx, ydy;
    pqi=0;
    // reset the node maps
    for(y=0;y<m;y++)
    {
        for(x=0;x<n;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    node no(xStart, yStart, 0, 0);
    no.updatePriority(xFinish, yFinish);
    pq[pqi].push_back(no);
    open_nodes_map[x][y]=no.getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        node n0( pq[pqi].front().getxPos(), pq[pqi].front().getyPos(), 
                     pq[pqi].front().getLevel(), pq[pqi].front().getPriority());

        x=n0.getxPos(); y=n0.getyPos();

        pq[pqi].erase(pq[pqi].begin()); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish) 
        {
            // generate the path from finish to start
            // by following the directions
            //String path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                //c='0'+(j+dir/2)%dir;
                //path=c+path;
				printf("%i ", (j+dir/2)%dir);
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            //delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].erase(pq[pqi].begin());
            //Serial.print("path:  ");
            //Serial.println(path);        
            //return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>n-1 || ydy<0 || ydy>m-1 || carte[xdx][ydy]==1 /*si il n'est pas occupé*/|| carte[xdx][ydy]==0/*s'il  n'est pas inexploré*/
                || closed_nodes_map[xdx][ydy]==1) || (xdx==xFinish & ydy==yFinish)/*si c'est la destination*/)
            {
                // generate a child node
                node m0( xdx, ydy, n0.getLevel(), 
                             n0.getPriority());
                m0.nextLevel();
                m0.updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0.getPriority();
                    pq[pqi].push_back(m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0.getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0.getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].front().getxPos()==xdx && 
                           pq[pqi].front().getyPos()==ydy))
                    {                
                        pq[1-pqi].push_back(pq[pqi].front());
                        pq[pqi].erase(pq[pqi].begin());       
                    }
                    pq[pqi].erase(pq[pqi].begin()); // remove the wanted node
                    
                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push_back(pq[pqi].front());
                        pq[pqi].erase(pq[pqi].begin());       
                    }
                    pqi=1-pqi;
                    pq[pqi].push_back(m0); // add the better node instead
                }
                //else delete m0; // garbage collection
            }
        }
        //delete n0; // garbage collection
    }
    return; // no route found
}





int main() {
	for (y = 0;y < m;y++) {
    	for(x = 0;x < n;x++) {
      		carte[x][y] = 0;
    	}
  	}
  	x = xStart;
  	y = yStart;
	pathFind(x,y,xFinish,yFinish);//calcul du trajet
}
