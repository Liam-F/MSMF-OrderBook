"""
BTREE
author: Tongda (Carl) Che
email: carlche@bu.edu
website: http://carlche15.github.com

"""
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import time


value1750=259.33
value2000=79.53
value2250=12.46
K_series=[2250,2000,1750]
value_series=[259.33,79.53,12.46]

# Parameter Settings:
True_value=[]
T=1.0 # time to maturity
N=np.arange(10,21) # steps series
r=0.0025 #risk-free rate
sigma=0.17 # volatility
K=2250 # strike series
X0=2000 # spot price

def Pay_off(x):
    global K
    return max(x-K,0)

class Binomial_Tree:
    def __init__(self,time_to_maturity,steps,risk_free_rate,sigma,strike,spot):
        self.dt=time_to_maturity/steps
        self.r=risk_free_rate
        self.sigma=sigma
        self.K=strike
        self.X0=spot
        self.t_steps=steps
        self.stock_tree=np.zeros([self.t_steps+1,2**(self.t_steps)])
        self.avg_tree=np.zeros([self.t_steps+1,2**(self.t_steps)])
        self.up_factor=np.exp(self.sigma*np.sqrt(self.dt))
        self.dn_factor=np.exp(-self.sigma*np.sqrt(self.dt))
        self.up_prob=(np.exp(r*self.dt)-self.dn_factor)/(self.up_factor-self.dn_factor)
        self.dn_prob=1.0-self.up_prob
        self.forward_constructor()
    def  forward_constructor(self):
    # constructing stock tree
       self.stock_tree[0,0]=self.X0
       for i in range(self.t_steps):
         for j in range(2**(i+1)):
                if(j%2==1):
                    self.stock_tree[i+1][j]=self.up_factor*self.stock_tree[i][(j-1)/2]
                else:
                    self.stock_tree[i+1][j]=self.dn_factor*self.stock_tree[i][(j/2)]
       self.avg_tree[0,0]=0.0
       for i in range(self.t_steps):
         for j in range(2 ** (i + 1)):
              if (j % 2 == 1):
                   self.avg_tree[i + 1][j] =(i/(i+1.0))*self.avg_tree[i][(j-1)/2]+(1/(i+1.0))*self.stock_tree[i+1][j]
              else:
                  self.avg_tree[i + 1][j] = (i / (i + 1.0)) * self.avg_tree[i][(j - 1) / 2] + (1 / (i + 1.0)) * self.stock_tree[i + 1][j]
    def backward_calculator(self,Pay_off):
        self.avg_tree[self.t_steps] = map(Pay_off, self.avg_tree[self.t_steps]) # calculate boundary first
        for i in range(self.t_steps,0,-1):
         for j in range(2**(i-1)):
           self.avg_tree[i-1][j]=np.exp(-self.r*self.dt)*(self.avg_tree[i][j*2+1]*self.up_prob+self.avg_tree[i][j*2]*self.dn_prob)


#
# tree=Binomial_Tree(T,20,r,sigma,K,X0)
# tree.backward_calculator(Pay_off)
# print tree.avg_tree[0][0]

"1st"
# mse_series=[]
# for i in  N:
#     tree = Binomial_Tree(T, i, r, sigma, K, X0)
#     tree.backward_calculator(Pay_off)
#     binomial_estimated_val=tree.avg_tree[0][0]
#     mse=(binomial_estimated_val-value2250)**2
#     mse_series.append(mse)
# plt.plot(N,np.log(mse_series),lw=2,color="dodgerblue")
# sns.set_style("whitegrid")
# plt.show()

"1st"
"2nd"
mse_series = []
time_series = []
for i in N:
  start_time=time.time()
  tree = Binomial_Tree(T, i, r, sigma, K, X0)
  tree.backward_calculator(Pay_off)
  binomial_estimated_val=tree.avg_tree[0][0]
  mse=(binomial_estimated_val-value2250)**2
  mse_series.append(mse)
  time_series.append(time.time()-start_time)
  plt.plot(time_series,np.log(mse_series),lw=3,color="red")

plt.xlabel("Running time (s)",fontsize=18)
plt.ylabel("Squared error",fontsize=18)
sns.set_style("whitegrid")
plt.legend(["K=2250"],fontsize=18)
plt.show()
"2nd"

