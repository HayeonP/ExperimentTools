# Autoware Analyzer
Calculate E2E(End-to-End) respnose time of instance chain and support plotting.

## How to use
1. Launch Autoware.
2. Execute `pose_diff_calculator` to get pose difference between vector map and current pose.
    ```
    cd ExperimentTools/pose_diff_calculator
    python3 pose_diff_calculator.py -o <pose_diff_filename>
    ```
3. Stop Autoware and `pose_diff_calculator`.
4. Set curret path to `ExperimentTools/autoware_analyzer/autoware_anlyzer.yaml`
    - `node_paths`
    Paths of nodes in instance chain.
    **Order of node should be same with instance.**
    - `pose_diff_path`
    Path of the pose difference file from `pose_diff_calculator`
    - `e2e_response_time_path`
    Path of the file that E2E response time information will be saved.
5. Execute `autoware_analyzer.py`
    ```
    python3 autoware_analyzer.py
    ```