package task1;

public class BoxTruck extends Truck {

    private Integer boxCount = 0;

    BoxTruck(String model) {
        this.model = model;
    }

    public void setBoxCount(Integer count) {
        this.boxCount = count;
    }

    public Integer getBoxCount() {
        return this.boxCount;
    }
}
