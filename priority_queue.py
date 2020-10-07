from dataclasses import dataclass

@dataclass
class Person:
    """Person Data Structure
    
    Attributes:
        name (str): Name of person
        priority (int): 
            Importance of person.
            Lower number equals higher priority.
    """
    name: str
    priority: int

@dataclass
class Node:
    """Node Data Structure
    
    Attributes:
        value (object): Stores name and priority of person
        next (object, None): Links to next node in the queue. Defaults to `None`.
    """
    value: object
    next: object = None
    
class PQueue:
    """Priorty Queue Implementation
    
    Priority queue implemented using a linked-list.
    Contains necessary methods associated with queues (enqueue, dequeue).
    Uses helper methods (queue_empty, queue_full) to carry out main methods.
    Traverse method used to print out entire linked list.
    
    Attributes:
        _queue_size (int): The maxiumum length of the queue
        _current_size (int): The current length of the queue
        _head (:obj:`Node`): A pointer to the first node in the linked list
    """
    def __init__(self, queue_size: int = 10):
        """Initialise Priority Queue

        Args:
            queue_size (int, optional): The maximum size of the queue. Defaults to 10.
        """
        self._queue_size = queue_size
        self._current_size = 0
        self._head = None
    
    def enqueue(self, value: Person) -> bool:
        """Enqueue Method

        Args:
            value (:obj:`Person`): value will be enqueued into priority queue

        Returns:
            bool: indicates if action was successful or unsuccessful (queue was full)
        """
        if self.queue_full():
            # unsuccessful action, queue was full
            return False
        # intialise head of queue to new value
        elif self.queue_empty():
            self._head = Node(value)
        # check if value priority exceeds head priority
        elif self._head.value.priority > value.priority:
            self._head = Node(value, self._head)
        else:
            # find node with lower index or until reached end of queue
            node_index = self._head
            while True:
                # check if node is end of queue
                if node_index.next == None:
                    break
                # check if next node has lower priority
                elif node_index.next.value.priority > value.priority:
                    break
                    
                node_index = node_index.next
            
            # insert new node into queue
            new_node = Node(value, node_index.next)
            node_index.next = new_node

        # update current length of queue
        self._current_size += 1
        
        return True
    
    def dequeue(self) -> [bool, Person]:
        """Dequeue Method

        Returns:
            [bool, Person]: 
                False, if dequeue was unsuccessful (queue was empty).
                Person, which was value dequeued from linked-list.
        """
        if self.queue_empty():
            # unsuccessful actio, queue was empty
            return False

        # create copy of head value
        return_value = self._head.value
        
        # delete head value, update linked-list
        if self._head.next:
            self._head = self._head.next
        else:
            self._head = None  
        
        # update current queue size
        self._current_size -= 1
        
        return return_value
        
    def queue_empty(self) -> bool:
        """Helper Method: checks if queue is empty

        Returns:
            bool:
                True, if queue is empty.
                False, if queue is not empty.
        """
        return self._head == None

    def queue_full(self) -> bool:
        """Helper Method: checks if queue is full

        Returns:
            bool: 
                True, if queue is full.
                False, if queue is not full. 
        """
        return self._current_size == self._queue_size
    
    def traverse(self):
        """Traverse Method
        
        Traverses through the queue, printing out each node.
        """
        if not self.queue_empty():
            # print all nodes whilst traversing through queue
            current_node = self._head
            
            # print all nodes in queue until end of queue
            while True:
                print(f"name: {current_node.value.name}, priority: {current_node.value.priority}")
                
                # check if end reached
                if current_node.next == None:
                    break
                
                # next node
                current_node = current_node.next
    
def main():
    """Main Function
    
    Tests methods in `PQueue` class
    """
    myQueue = PQueue(5)
    
    # list of names and priorities
    names =  ["Aman", "Tom", "Pratyush", "Dawud", "Mr. Wood", "Unknown"]
    priorities = [2, 3, 5, 2, 1, 3]
    
    # enqueue persons into queue - reject `Unknown`
    for i in range(len(names)):
        person = Person(names[i], priorities[i])
        myQueue.enqueue(person)
    myQueue.traverse()
    print()
    
    # dequeue first 2 nodes in queue - queue left with 3 nodes
    for i in range(2):
        myQueue.dequeue()
    myQueue.traverse()
    print()

    # dequeue entire queue - rejects dequeues when queue is empty
    for i in range(100):
        myQueue.dequeue()
    myQueue.traverse()
    print()
    
if __name__ == "__main__":
    main()