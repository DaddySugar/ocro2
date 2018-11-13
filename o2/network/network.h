# ifndef NETWORK_H
# define NETWORK_H


/**
 * \struct s_network
 * \brief The structure of a neural network
 */
struct s_network
{
  unsigned nblayer; /*!< The number of layer */
  unsigned *layers; /*!< The number of neurone for each layer */
  float **threshold; /*!< The threshold or bias of the neural network */
  float **out; /*!< The activation value of each neurone */
  float **delta; /*!< The deltas of each neurone */
  float ***weight; /*!< The weight of each neurone */
};

typedef struct s_network network;


network *newNetwork(unsigned  nblayer, unsigned *layers);
void freeNetwork(network *n);
network *loadNetwork(char *path);
void saveNetwork(char *path, network *n);
void generateNetwork();
void feedForward(network *n, float *inputs);
void backPropagation(network *n, float *outputs);
void update(network *n, float speed); 
float evaluate(network *n, float **samples, float **results, size_t nbSample); 

# endif