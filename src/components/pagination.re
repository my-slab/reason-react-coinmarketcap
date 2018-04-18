type step =
  | Next(int, int)
  | Previous(int, int);

let component = ReasonReact.statelessComponent("Pagination");

let step = action => {
  let page_size = 100;
  (
    switch action {
    | Next(limit, offset) =>
      let limit = string_of_int(limit);
      let offset = string_of_int(offset + page_size);
      (limit, offset);
    | Previous(limit, offset) =>
      let limit = string_of_int(limit);
      let offset =
        string_of_int(offset - page_size < 0 ? 0 : offset - page_size);
      (limit, offset);
    }
  )
  |> (((limit, offset)) => "?limit=" ++ limit ++ "&offset=" ++ offset);
};

let make = (~limit: int, ~offset: int, _children) => {
  ...component,
  render: _self =>
    <div>
      <ul className="pagination">
        <li
          className="link"
          onClick=(
            event => {
              ReactEventRe.Mouse.preventDefault(event);
              Next(limit, offset) |> step |> ReasonReact.Router.push;
            }
          )>
          <Text value="Next 100" />
        </li>
        <li
          className="link"
          onClick=(
            event => {
              ReactEventRe.Mouse.preventDefault(event);
              Previous(limit, offset) |> step |> ReasonReact.Router.push;
            }
          )>
          <Text value="Previous 100" />
        </li>
      </ul>
    </div>
};