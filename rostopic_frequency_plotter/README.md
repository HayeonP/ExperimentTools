#Rostopic Frequency Plotter

## How to Use
1. Record tostopic hz for target topic
```
$ rostopic hz -w 2 <target_topic_name> > hz.csv
```
2. Move output to data directory
```
$ mv hz.csv <workspce>/data/hz.csv
```
3. Run script
```
$ python3 rostopic_frequency_plotter.py
```