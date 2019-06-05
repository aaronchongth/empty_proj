import numpy as np


class Episode:
    states = []
    actions = []


class OnPolicyMonteCarlo:
    def __init__(self, n_states, n_actions, rewards, discount=0.9, 
                 epsilon=0.05):
        self.n_states = n_states
        self.n_actions = n_actions
        self.action_value = np.random.rand(n_states, n_actions)

        self.epsilon = epsilon
        self.soft_policy = np.zeros(n_states, n_actions)
        self.soft_policy_from_action_value()

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

      
    def soft_policy_from_action_value(self):
        for s in range(self.n_states):
            curr_row = self.action_value[s]
            greedy_action = np.argmax(curr_row)

            for a in range(self.n_actions):
                if a != greedy_action:
                    self.soft_policy[s][a] = self.epsilon
                else:
                    self.soft_policy[s][a] = 1 - \
                            (self.n_actions - 1) * self.epsilon


    def get_action_from_soft_policy(self, curr_state):
        state_actions = self.soft_policy[curr_state]
        return np.random.choice(self.n_actions, p=state_actions)


    def generate_episode(self):
        episode = Episode()
        episode.states = [self.start_state]
        episode.actions = []

        curr_state = episode.states[-1]
        while curr_state != self.end_state:
            curr_state = episode.states[-1]
            curr_action = self.get_action_from_soft_policy(curr_state)
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
            current_episode = self.generate_episode()
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
            self.soft_policy_from_action_value()
