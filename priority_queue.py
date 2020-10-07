from dataclasses import dataclass

@dataclass
class Person:
    name: str
    priority: int

@dataclass
class Node:
    value: object
    next: object = None
    
class PQueue:
    def __init__(self, queue_size: int = 10):
        self._queue_size = queue_size
        self._current_size = 0
        self._head = None
        self._tail = None
    
    def enqueue(self, value: Person):
        if self.queue_full():
            return False
        elif self.queue_empty():
            self._head = Node(value)
        elif self._head.value.priority > value.priority:
            self._head = Node(value, self._head)
        else:
            node_index = self._head
            while True:
                if node_index.next == None:
                    break
                elif node_index.next.value.priority > value.priority:
                    break
                    
                node_index = node_index.next
                
            new_node = Node(value, node_index.next)
            
            node_index.next = new_node

        self._current_size += 1
        return True
    
    def dequeue(self):
        if self.queue_empty():
            return False
        
        return_value = self._head.value
        
        
        if self._head.next:
            self._head.value = self._head.next.value
            self._head.next = self._head.next.next  
        else:
            self._head = None  
        
        return return_value
        
    def queue_empty(self) -> bool:
        return self._head == None

    def queue_full(self) -> bool:
        return self._current_size == self._queue_size
    
    def traverse(self):
        if not self.queue_empty():
            tmpPtr = self._head
            while tmpPtr.next != None:
                print(f"name: {tmpPtr.value.name}, priority: {tmpPtr.value.priority}")
                tmpPtr = tmpPtr.next
            print(f"name: {tmpPtr.value.name}, priority: {tmpPtr.value.priority}")
    
def main():
    names =  ["Aman", "Tom", "Pratyush", "Dawud", "Mr. Wood"]
    priorities = [2, 3, 5, 2, 1]
    
    myQueue = PQueue(6)
    
    for i in range(len(names)):
        person = Person(names[i], priorities[i])
        myQueue.enqueue(person)
        
    myQueue.traverse()
    
    for i in range(2):
        myQueue.dequeue()
    
    print()
    myQueue.traverse()

    for i in range(100):
        myQueue.dequeue()
    
    print()
    myQueue.traverse()
    
if __name__ == "__main__":
    main()