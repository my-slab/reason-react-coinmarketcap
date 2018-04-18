type search = {
  offset: int,
  limit: int
};

type action =
  | Navigate(search);

type state = {search};

let parse_value = (elem, ~default) =>
  try (int_of_string(elem)) {
  | Failure(_reason) => default
  };

let parse_search = (search: string) : search =>
  Js.String.split("&", search)
  |> Array.to_list
  |> List.fold_left(
       (acc, elem) =>
         elem
         |> Js.String.split("=")
         |> Array.to_list
         |> (
           split =>
             switch split {
             | ["offset", value] => {
                 ...acc,
                 offset: parse_value(value, ~default=0)
               }
             | ["limit", value] => {
                 ...acc,
                 limit: parse_value(value, ~default=100)
               }
             | _ => acc
             }
         ),
       {limit: 0, offset: 0}
     );

let component = ReasonReact.reducerComponent("Page");

let make = (~title: string, _children) => {
  ...component,
  initialState: () => {offset: 0, limit: 100},
  reducer: (action, _state) =>
    switch action {
    | Navigate(search) => ReasonReact.Update(search)
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url => {
          let result = url.search |> parse_search;
          Navigate(result) |> self.send;
        }),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self =>
    <div>
      <div> <h1> <Text value=title /> </h1> </div>
      <Table limit=self.state.limit offset=self.state.offset />
      <br />
      <Pagination limit=self.state.limit offset=self.state.offset />
    </div>
};