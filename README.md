# AlgorithmGC
GC Algorithm Results in Community Detection on Some Collaborative Networks

## Results of Non-Overlapping Community Detection

<table align="center" border="0" cellspacing="4">
  <tr>
    <th rowspan="2">DataSet</th> <th rowspan="2">Nodes</th> <th rowspan="2">Edges</th>
    <th colspan="2">GC</th> <th colspan="2">InfoMAP</th> <th colspan="2">LPA</th> <th colspan="2">WALKTRAP</th>
  </tr>
  <tr align="center">
    <td>nums</td> <td>Q</td> <td>nums</td> <td>Q</td> <td>nums</td> <td>Q</td> <td>nums</td> <td>Q</td>
  </tr>
  <tr align="right">
    <td align="center">arXiv(AC)</td> <td align="center">651</td> <td align="center">1355</td>
    <td> 50</td> <td>0.7631</td> <td>100</td> <td>0.7465</td>
    <td> 89</td> <td>0.7604</td> <td> 86</td> <td>0.7658</td>
  </tr>
  <tr align="right">
    <td align="center">crime(MC)</td> <td align="center">754</td> <td align="center">2127</td> 
    <td> 18</td> <td>0.8318</td> <td> 78</td> <td>0.8196</td> 
    <td> 83</td> <td>0.8047</td> <td> 56</td> <td>0.8476</td>
  </tr>
  <tr align="right">
    <td align="center">DBLP(PA)</td> <td align="center">117</td> <td align="center">300</td> 
    <td>  8</td> <td>0.6004</td> <td> 16</td> <td>0.6237</td> 
    <td>  8</td> <td>0.5914</td> <td> 10</td> <td>0.6128</td>
  </tr>
  <tr align="right">
    <td align="center">writers(WR)</td> <td align="center">1771</td> <td align="center">13502</td> 
    <td> 29</td> <td>0.7419</td> <td>157</td> <td>0.7760</td> 
    <td>167</td> <td>0.7727</td> <td>264</td> <td>0.7574</td>
  </tr>
</table>

## Results of Overlapping Community Detection

<table align="center" border="0" cellspacing="4">
  <tr>
    <th rowspan="2">DataSet</th> <th rowspan="2">Nodes</th> <th rowspan="2">Edges</th>
    <th colspan="2">GC</th> <th colspan="2">COPRA</th> <th colspan="2">SLPA</th> <th colspan="2">LFM</th>
  </tr>
  <tr align="center">
    <td>nums</td> <td>EQ</td> <td>nums</td> <td>EQ</td> <td>nums</td> <td>EQ</td> <td>nums</td> <td>EQ</td>
  </tr>
  <tr align="right">
    <td align="center">arXiv(AC)</td> <td align="center">651</td> <td align="center">1355</td>
    <td> 49</td> <td>0.6376</td> <td> 88</td> <td>0.6070</td>
    <td> 97</td> <td>0.6466</td> <td>135</td> <td>0.5693</td>
  </tr>
  <tr align="right">
    <td align="center">crime(MC)</td> <td align="center">754</td> <td align="center">2127</td> 
    <td> 19</td> <td>0.7794</td> <td> 88</td> <td>0.7547</td> 
    <td> 97</td> <td>0.7557</td> <td>119</td> <td>0.6881</td>
  </tr>
  <tr align="right">
    <td align="center">DBLP(PA)</td> <td align="center">117</td> <td align="center">300</td> 
    <td>  9</td> <td>0.5805</td> <td>  9</td> <td>0.5572</td> 
    <td> 15</td> <td>0.5110</td> <td> 16</td> <td>0.5637</td>
  </tr>
  <tr align="right">
    <td align="center">writers(WR)</td> <td align="center">1771</td> <td align="center">13502</td> 
    <td> 68</td> <td>0.7460</td> <td>157</td> <td>0.7710</td> 
    <td>156</td> <td>0.7600</td> <td>236</td> <td>0.7392</td>
  </tr>
</table>