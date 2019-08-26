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
    <td>50</td> <td>0.7631</td> <td>100</td> <td>0.746492</td>
    <td>89</td> <td>0.760374</td> <td>86</td> <td>0.765762</td>
  </tr>
  <tr align="right">
    <td align="center">crime(MC)</td> <td align="center">754</td> <td align="center">2127</td> 
    <td>18</td> <td>0.8318</td> <td>78</td> <td>0.81957</td> 
    <td>83</td> <td>0.804739</td> <td>56</td> <td>0.847618</td>
  </tr>
  <tr align="right">
    <td align="center">DBLP(PA)</td> <td align="center">117</td> <td align="center">300</td> 
    <td>8</td> <td>0.60041</td> <td>16</td> <td>0.623706</td> 
    <td>8</td> <td>0.591361</td> <td>10</td> <td>0.612844</td>
  </tr>
  <tr align="right">
    <td align="center">writers(WR)</td> <td align="center">1771</td> <td align="center">13502</td> 
    <td>29</td> <td>0.74188</td> <td>157</td> <td>0.776015</td> 
    <td>167</td> <td>0.772685</td> <td>264</td> <td>0.757439</td>
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
    <td>49</td> <td>0.637608</td> <td>88</td> <td>0.606969</td>
    <td>97</td> <td>0.646603</td> <td>135</td> <td>0.569307</td>
  </tr>
  <tr align="right">
    <td align="center">crime(MC)</td> <td align="center">754</td> <td align="center">2127</td> 
    <td>19</td> <td>0.779417</td> <td>88</td> <td>0.75468</td> 
    <td>97</td> <td>0.755672</td> <td>119</td> <td>0.688126</td>
  </tr>
  <tr align="right">
    <td align="center">DBLP(PA)</td> <td align="center">117</td> <td align="center">300</td> 
    <td>9</td> <td>0.580468</td> <td>9</td> <td>0.557236</td> 
    <td>15</td> <td>0.510997</td> <td>16</td> <td>0.563689</td>
  </tr>
  <tr align="right">
    <td align="center">writers(WR)</td> <td align="center">1771</td> <td align="center">13502</td> 
    <td>68</td> <td>0.745955</td> <td>157</td> <td>0.770993</td> 
    <td>156</td> <td>0.759979</td> <td>236</td> <td>0.739162</td>
  </tr>
</table>