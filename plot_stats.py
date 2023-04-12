import matplotlib.pyplot as plt
import numpy as np
import os

LOGS_DIR = './Logs'

def DrawLogs( dir_name ):
  # Read logs
  agent_data = dict()

  files = os.listdir( dir_name )
  fig, axes = plt.subplots(figsize=(20, 10))
  for agent in files:
    print('processing %s''s data' % agent)  
    filename = os.path.join( dir_name, agent )
    agent_data[agent] = []
    with open( filename , 'r') as f:
        agent_data[agent] = list(map(lambda x: float(x), f.readlines()))
  
    data_len = len(agent_data[agent])
    x = np.linspace(0, data_len, 1)
    sample_cnt = 10000
    
    # agent_data is the raw data.  We are going to plot the average reward. 
    plot_data = []
    if sample_cnt < len(agent_data[agent]):
      plot_data = [agent_data[agent][i] for i in range(0, len(agent_data[agent]), len(agent_data[agent]) / sample_cnt)] 
    else:
      plot_data = agent_data[agent]

    sum = 0
    for i in range(len(plot_data)):
      sum += plot_data[i]
      plot_data[i] = float(sum) / (i+1)
    
    plt.plot( plot_data, label = agent )

  plt.legend(loc='lower right')
  #plt.show()
  plt.draw()
  plt.subplots_adjust(left=0.03, right=0.98, top = 0.95, bottom=0.03)
  plt.pause(1)
  input('<Hit Enter To close>')
  plt.close(fig)

DrawLogs(LOGS_DIR)
