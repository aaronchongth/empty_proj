import numpy as np

class MonteCarlo:
    def __init__(self, n_states, n_actions):
        self.n_states = n_states
        self.n_actions = n_actions
        self.action_value = np.random.rand(n_states, n_actions)

        self.greedy_policy = np.zeros(n_states, np.int32)
        self.greedy_policy_from_action_value()

        self.soft_policy = np.random.rand(n_states, n_actions)
        self.normalize_matrix_column(self.soft_policy)
        
        self.start_state = 0
        self.end_state = n_states - 1
        
        # handle transition matrix

    def greedy_policy_from_action_value(self):
        for r in range(self.action_value.shape[0]):
            curr_row = self.action_value[r]
            self.greedy_policy[r] = np.argmax(curr_row)

    
    def normalize_matrix_column(self, matrix):
        for r in range(matrix.shape[0]):
            curr_row = matrix[r]
            matrix[r] /= sum(curr_row)
            assert sum(matrix[r]) >= 0.9999 and sum(matrix[r]) <= 1.0001


    def generate_greedy_episode(self):
        curr_state = self.start_state
        curr_iter = 0
        max_iter = 1000

        states = []
        actions = []
        while curr_state != self.end_state and curr_iter < max_iter:
            states.append(curr_state)
            curr_action
            curr_iter += 1


        raise NotImplementedError

    
    def generate_soft_episode(self):
        raise NotImplementedError


    def main(self):
        n_episodes = 1000
        for i in range(n_episodes):
            current_episode = self.generate_greedy_episode()

