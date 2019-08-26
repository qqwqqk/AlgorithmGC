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
    <td> 50</td> <td>0.76310</td> <td>100</td> <td>0.74649</td>
    <td> 89</td> <td>0.76037</td> <td> 86</td> <td>0.76576</td>
  </tr>
  <tr align="right">
    <td align="center">crime(MC)</td> <td align="center">754</td> <td align="center">2127</td> 
    <td> 18</td> <td>0.83180</td> <td> 78</td> <td>0.81957</td> 
    <td> 83</td> <td>0.80474</td> <td> 56</td> <td>0.84762</td>
  </tr>
  <tr align="right">
    <td align="center">DBLP(PA)</td> <td align="center">117</td> <td align="center">300</td> 
    <td>  8</td> <td>0.60041</td> <td> 16</td> <td>0.62371</td> 
    <td>  8</td> <td>0.59136</td> <td> 10</td> <td>0.61284</td>
  </tr>
  <tr align="right">
    <td align="center">writers(WR)</td> <td align="center">1771</td> <td align="center">13502</td> 
    <td> 29</td> <td>0.74188</td> <td>157</td> <td>0.77602</td> 
    <td>167</td> <td>0.77269</td> <td>264</td> <td>0.75744</td>
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
    <td> 49</td> <td>0.63761</td> <td> 88</td> <td>0.60697</td>
    <td> 97</td> <td>0.64660</td> <td>135</td> <td>0.56931</td>
  </tr>
  <tr align="right">
    <td align="center">crime(MC)</td> <td align="center">754</td> <td align="center">2127</td> 
    <td> 19</td> <td>0.77942</td> <td> 88</td> <td>0.75468</td> 
    <td> 97</td> <td>0.75567</td> <td>119</td> <td>0.68813</td>
  </tr>
  <tr align="right">
    <td align="center">DBLP(PA)</td> <td align="center">117</td> <td align="center">300</td> 
    <td>  9</td> <td>0.58047</td> <td>  9</td> <td>0.55724</td> 
    <td> 15</td> <td>0.51100</td> <td> 16</td> <td>0.56369</td>
  </tr>
  <tr align="right">
    <td align="center">writers(WR)</td> <td align="center">1771</td> <td align="center">13502</td> 
    <td> 68</td> <td>0.74596</td> <td>157</td> <td>0.77099</td> 
    <td>156</td> <td>0.75998</td> <td>236</td> <td>0.73916</td>
  </tr>
</table>