import cv2
import threading
import queue
import numpy as np
import time

class CustomVideoCapture:

    def __init__(self, source) -> None:
        """ Конструктор принимает
        * source - источник
        
        Параметры, которые можно менять:

        * number_thread  - количество потоков;
        * len_queue - количество изображений в очереди.
        
        
        """
        self.cap = cv2.VideoCapture(source)
        self.queue = queue.Queue()
        self.number_thread = 1
        self.len_queue = 1
        self.list_thread = []
        self.flag = 0
        self.stop_threads = False

    
    def readframe(self) -> None:
        """ Функция чтения кадра"""
        while not self.stop_threads:
            ret, img = self.cap.read()
            if self.queue.qsize() > self.len_queue:
                with self.queue.mutex:
                    self.queue.queue.clear()
            if ret:
                self.queue.put(img)

    def read(self) -> np.ndarray:
        """Чтение последнего кадра с видео потока.
        """

        if self.flag == 0:
            for i in range(self.number_thread):
                thread = threading.Thread(target=self.readframe)
                self.list_thread.append(thread)
                thread.start()
            self.flag = 1

        try:
            img = self.queue.get_nowait()
        except: img = None
        if img is not None:
            return True, img
        return False, img

    def release(self) -> None:
        """Освобождение потока"""
        self.stop_threads = True
        for thread in self.list_thread:
            thread.join()
        self.cap.release()
        del self.queue
    
    def __del__(self):
        pass


"""
Пример использования ниже
"""

if __name__ == '__main__':
    custom_video_capture = CustomVideoCapture(0)
    time_start = 0
    try:
        while True:
            success, frame = custom_video_capture.read()
            if success:
                fps = 1 / (time.time() - time_start)
                cv2.imshow("frame", frame)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
                time_start = time.time()
                print(fps)
    except KeyboardInterrupt:  
        pass
    finally:
        custom_video_capture.release()
        cv2.destroyAllWindows()

