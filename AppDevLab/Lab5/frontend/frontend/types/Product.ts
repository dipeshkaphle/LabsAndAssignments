export default interface Product {
    _id: string;
    name: string;
    producer: string;
    description: string;
    category: string;
    price: number;
    bought_count: number;
    stock_count: number;
}