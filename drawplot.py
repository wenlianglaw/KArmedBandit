import matplotlib.pyplot as plt
import numpy as np
import os

LOGS_DIR = './Logs'

def DrawLogs( dir_name ):
  # Read logs
  agent_data = dict()

  files = os.listdir( dir_name )
  for agent in files:
    print('processing %s' % agent)  
    filename = os.path.join( dir_name, agent )
    agent_data[agent] = []
    with open( filename , 'r') as f:
        agent_data[agent] = list(map(lambda x: float(x), f.readlines()))
  
    data_len = len(agent_data[agent])
    x = np.linspace(0, data_len, 1)
    # Only print X points, otherwise the plot will be too dense
    sample_cnt = 500
    if sample_cnt < len(agent_data[agent]):
      plt.plot( [agent_data[agent][i] for i in range(0, len(agent_data[agent]), len(agent_data[agent]) / sample_cnt)], 
            label = agent)
    else:
      plt.plot( agent_data[agent], label = agent )

  plt.legend()
  plt.show()


DrawLogs(LOGS_DIR)
