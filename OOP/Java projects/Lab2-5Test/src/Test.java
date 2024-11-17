// Родительский класс Animal
class Animal {
    protected String name;

    // Конструктор класса Animal
    public Animal(String name) {
        this.name = name;
    }

    // Метод, который выводит звук животного
    public void makeSound() {
        System.out.println("Животное издаёт звук.");
    }

    // Метод, который возвращает имя животного
    public String getName() {
        return this.name;
    }
}

// Класс-наследник Dog
class Dog extends Animal {

    // Конструктор класса Dog
    public Dog(String name) {
        // Используем super для вызова конструктора родительского класса Animal
        super(name);
    }

    // Переопределяем метод makeSound() с использованием super
    @Override
    public void makeSound() {
        // Вызов метода родительского класса через super
        super.makeSound();
        // Добавляем новую логику для класса Dog
        System.out.println("Собака лает: Гав-гав!");
    }

    // Дополнительный метод для класса Dog
    public void wagTail() {
        System.out.println(this.name + " виляет хвостом.");
    }
}



public class Test {
    public static void main(String[] args) {
        // Создаём объект класса Dog
        Dog dog = new Dog("Барбос");

        // Вызов метода, который использует super
        dog.makeSound();  // Сначала вызовется метод родительского класса, затем дочернего

        // Вызов дополнительного метода класса Dog
        dog.wagTail();  // "Барбос виляет хвостом."
    }
}
