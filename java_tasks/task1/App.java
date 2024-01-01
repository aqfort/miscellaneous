package task1;

public class App {
    public static void main(String[] args) throws Exception {

        System.out.println("Hello, World!");
        System.out.println("");

        BoxTruck truck = new BoxTruck("Peterbilt 337");
        truck.start();
        truck.drive(50);
        System.out.println("Speed: " + truck.getSpeed());
        truck.stop();
        System.out.println("Speed: " + truck.getSpeed());

        if (truck.isLoaded()) {
            System.out.println(truck.model + " is loaded: " + truck.weight());
        } else {
            System.out.println(truck.model + " is not loaded");
        }

        System.out.println("");

        SportsCar supra = new SportsCar("Toyota Supra MK4");
        supra.setPilot("Paul");
        supra.tune(3);

        if (supra.isStock()) {
            System.out.println("Magic: " + supra.model + " is stock");
        } else {
            System.out.println("Obviously, this " + supra.model + " is not stock");
        }

        supra.start();
        supra.drive(260);
        System.out.println("Speed: " + supra.getSpeed());
        supra.stop();
        System.out.println("Speed: " + supra.getSpeed());

        System.out.println("Pilot: " + supra.getPilot());
    }
}
