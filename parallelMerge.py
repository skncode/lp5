import multiprocessing

def merge_sort(arr, queue):
    if len(arr) <= 1:
        queue.put(arr)
        return

    mid = len(arr) // 2
    left = arr[:mid]
    right = arr[mid:]

    left_queue = multiprocessing.Queue()
    right_queue = multiprocessing.Queue()

    left_process = multiprocessing.Process(target=merge_sort, args=(left, left_queue))
    right_process = multiprocessing.Process(target=merge_sort, args=(right, right_queue))

    left_process.start()
    right_process.start()

    left_process.join()
    right_process.join()

    left_sorted = left_queue.get()
    right_sorted = right_queue.get()

    queue.put(merge(left_sorted, right_sorted))

def merge(left, right):
    merged = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    merged.extend(left[i:])
    merged.extend(right[j:])
     

    return merged

if __name__ == '__main__':
    arr = [5, 3, 8, 4, 2, 1, 9, 6, 7]
    print("Original array:", arr)

    queue = multiprocessing.Queue()
    merge_sort(arr, queue)
    sorted_arr = queue.get()

    print("Sorted array:", sorted_arr)