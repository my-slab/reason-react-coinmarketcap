type route =
  | List;

type action =
  | Navigate(route);

type state = {route};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {route: List},
  reducer: (action, _state) =>
    switch action {
    | Navigate(List) => ReasonReact.Update({route: List})
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch url.path {
          | _ => self.send(Navigate(List))
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self =>
    <div>
      (
        switch self.state.route {
        | List => <Page title="Cryptocurrency Market Capitalizations" />
        }
      )
    </div>
};