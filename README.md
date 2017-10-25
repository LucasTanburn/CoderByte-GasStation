# CoderByte-GasStation

Please note that I use the word "gas" instead of "petrol" in this challenge because that's how I read the challenge and I'm not going back to change everything now.

The challenge is to find whether or not it is possible to traverse a loop of gas stations with a limited supply.  
The input is an array, in this case taken directly from the code, where the first element is the number of gas stations in the loop. The remaining elements are integers, seperated by a colon with the first integer representing the amount of gas gained from the station and the second integer representing the amount of gas needed to get to the next station, for example:
```
{"2","1:3","3:1"}
```
This array shows that there are 2 stations in the loop, the first supplies 1 unit of gas and requires 3 to get to the next station, the second station supplies 3 units of gas and requires 1 unit to get back to the first. In this particular example it is not possilbe to traverse the loop starting from the first station, but it is possible starting from the second station.  
  
The output is a string that shows which station it is possible to start at to complete the entire loop back to the original station, so in the example it would output "2". If it is possible to start from more than one station, it will show the first station from which it could start. If the loop cannot be completed from any station it should return "impossible"
