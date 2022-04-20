import { Pagination } from "react-bootstrap";

export default function Paginate(props: {
  active: number;
  total: number;
  setActive: (page: number) => void;
}) {
  const { active, total, setActive } = props;
  return (
    <Pagination>
      <Pagination.Prev
        onClick={() => setActive(active - 1 === -1 ? active : active - 1)}
      />
      <Pagination.Item active>{active}</Pagination.Item>
      <Pagination.Next
        onClick={() => setActive(active + 1 === total ? active : active + 1)}
      />
    </Pagination>
  );
}
