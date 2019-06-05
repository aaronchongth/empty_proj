import numpy as np


class Episode:
    states = []
    actions = []


class MonteCarloExploring:
    def __init__(self, n_states, n_actions, rewards, discount=0.9):
        self.n_states = n_states
        self.n_actions = n_actions
        self.action_value = np.random.rand(n_states, n_actions)

        self.greedy_policy = np.zeros(n_states, np.int32)
        self.greedy_policy_from_action_value()

        self.start_state = 0
        self.end_state = n_states - 1
        
        self.transition_matrix = np.random.rand(n_states, n_actions, n_states)
        self.normalize_matrix_axis(self.soft_policy, 1)

        self.rewards = rewards # n_states x n_actions
        self.discount = discount
        self.returns = []
        for i in range(n_states):
            curr_state_list = []
            for j in range(n_actions):
                curr_state_list.append([])
            self.returns.append(curr_state_list)


    def greedy_policy_from_action_value(self):
        for r in range(self.action_value.shape[0]):
            curr_row = self.action_value[r]
            self.greedy_policy[r] = np.argmax(curr_row)

    
    def normalize_matrix_axis(self, matrix, axis):
        if axis == matrix.shape[-1]:
            print('Cannot normalize the last axis of the matrix.')
            raise RuntimeError

        for r in range(matrix.shape[axis]):
            curr_parent_axis = matrix[r]
            matrix[r] /= sum(curr_parent_axis)
            assert sum(matrix[r]) >= 0.9999 and sum(matrix[r]) <= 1.0001

    
    def get_action_from_greedy_policy(self, curr_state):
        return self.greedy_policy[curr_state]


    def generate_greedy_episode(self):
        episode = Episode()
        episode.states = [self.start_state]
        episode.actions = []

        curr_state = episode.states[-1]
        while curr_state != self.end_state:
            curr_state = episode.states[-1]
            curr_action = self.get_action_from_greedy_policy(curr_state)
            episode.actions.append(curr_action)

            possible_next_states = self.transition_matrix[curr_state][curr_action]
            next_state = np.random.choice(possible_next_states.shape[0],
                                          p=possible_next_states)
            episode.states.append(next_state)
            curr_iter += 1
        return episode


    def get_episode_instance_return(self, episode, index):
        curr_instance_return = 0
        discount_iter = 0
        for i in range(index, len(episode.actions)):
            curr_state = episode.states[i]
            curr_action = episode.actions[i]
            curr_instance_return += (self.discount ** discount_iter) * \
                    self.rewards[curr_state][curr_action]
        return curr_instance_return


    def main(self):
        n_episodes = 1000
        for i in range(n_episodes):
            current_episode = self.generate_greedy_episode()
            visited_state_action_pairs = np.zeros([self.n_states, 
                                                   self.n_actions], 
                                                  np.bool)
            
            # every state action pair, update returns
            for action_index in range(len(current_episode.actions)):
                state = current_episode.states[action_index]
                action = current_episode.states[action_index]

                if visited_state_action_pairs[state][action]:
                    continue

                instance_return = \
                        self.get_episode_instance_return(current_episode,
                                                          action_index)
                self.returns[state][action].append(instance_return)
                visited_state_action_pairs[state][action] = True

                self.action_value[state][action] = \
                        np.average(self.returns[state][action])
                
            # generate greedy policy again for next episode
            self.greedy_policy_from_action_value()

            
